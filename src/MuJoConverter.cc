//
// Created by hjzh on 18-3-2.
//

#include "MuJoConverter.h"
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include <cstring>

using namespace rapidxml;

MuJoConverter::MuJoConverter(std::string input, std::string output, std::string keyPath) {
  m_in = input;
  m_out = output;
  m_keyPath = keyPath;
}

MuJoConverter::~MuJoConverter() {
  mj_deactivate();
}

FileType MuJoConverter::filetype(std::string file_name) {
  size_t last_dot_pos = file_name.find_last_of('.');
  if (last_dot_pos == std::string::npos) {
    return FILE_UNKNOWN;
  }

  if (file_name.substr(last_dot_pos + 1, file_name.length() - last_dot_pos - 1) == std::string("xml")) {
    return FILE_XML;
  }

  if (file_name.substr(last_dot_pos + 1, file_name.length() - last_dot_pos - 1) == std::string("urdf")) {
    return FILE_URDF;
  }

  return FILE_UNKNOWN;
}

bool MuJoConverter::Init() {
  if (0 == mj_activate(m_keyPath.c_str())) {
    return false;
  }

  if (filetype(m_in) != FILE_URDF || filetype(m_out) != FILE_XML) {
    return false;
  }

  return true;
}

bool MuJoConverter::Convert() {
  if (!LoadModel()) {
    std::cout << "muJoConverter failed to load model from input file" << std::endl;
    return false;
  }

  if (!SaveModel()) {
    std::cout << "muJoConverter failed to save model to output file" << std::endl;
    return false;
  }

  /// Using RapidXML reload the MJCF file and insert some elements
  xml_document<> doc;
  std::ifstream MJCFFile(m_out.c_str());
  std::stringstream buffer;
  buffer << MJCFFile.rdbuf();
  MJCFFile.close();
  std::string content(buffer.str());
  std::vector<char> content_xml_vector(content.begin(), content.end());
  content_xml_vector.push_back('\0');
  doc.parse<0>(content_xml_vector.data());

  /// Add light to the MJCF file
  /// You need to maintain the lifetime of xml str as long as the lifetime of rapidxml doc
  std::string light_xml_str = R"(<light directional="false" cutoff="90" exponent="1" diffuse="1 1 1" specular="0 0 0" pos="1 0 1.5" dir="-1 0 -2.5"/>)";
  std::vector<char> light_xml_vector(light_xml_str.begin(), light_xml_str.end());
  light_xml_vector.push_back('\0');

  std::string ground_xml_str = R"(<geom name="ground" type="plane" pos="0 0 -0.925" size="4 4 .05" rgba="0.7 0.6 0.5 1"/>)";
  std::vector<char> ground_xml_vector(ground_xml_str.begin(), ground_xml_str.end());
  ground_xml_vector.push_back('\0');

  AddLightToMJCF(doc, light_xml_vector.data(), ground_xml_vector.data());

  /// Save modified MJCF file
  std::ofstream file_stored(m_out.c_str());
  file_stored << doc;
  file_stored.close();
  doc.clear();
}

bool MuJoConverter::LoadModel() {
  if (m_model.Load(m_in) != 0) {
    return false;
  }
  return true;
}

bool MuJoConverter::SaveModel() {
  if (m_model.Save(m_out) != 0) {
    return false;
  }
  return true;
}

bool MuJoConverter::AddLightToMJCF(xml_document<>& doc, char *light_data, char *ground_data) {
  /// Get worldbody node in doc
  xml_node<> *pMuJoCo = doc.first_node("mujoco");
  if (!pMuJoCo) {
    return false;
  }
  xml_node<> *pWorldBody = pMuJoCo->first_node("worldbody");
  if (!pWorldBody) {
    return false;
  }

  /// Insert light element if doesn't have it
  if (!pWorldBody->first_node("light")) {
    /// Get a copy light node first
    xml_document<> light_xml_doc;
    // std::cout << light_xml_vector.data() << std::endl;
    light_xml_doc.parse<0>(light_data);
    xml_node<> *light_xml_node = light_xml_doc.first_node();
    /// This is the node which will be added to doc
    xml_node<> *light_copy_node = doc.clone_node(light_xml_node);
    pWorldBody->append_node(light_copy_node);
  }

  /// Insert ground element if doesn't have it
  xml_node<> *pGeom = pWorldBody->first_node("geom");
  while (pGeom) {
    if (pGeom->first_attribute("name")->value() == "ground") {
      break;
    }
    pGeom = pGeom->next_sibling("geom");
  }
  if (!pGeom) {
    xml_document<> ground_xml_doc;

    ground_xml_doc.parse<0>(ground_data);
    xml_node<> *xml_node_ground = ground_xml_doc.first_node();
    xml_node<> *ground_copy_node = doc.clone_node(xml_node_ground);
    pWorldBody->append_node(ground_copy_node);
  }
}