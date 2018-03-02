//
// Created by hjzh on 18-3-2.
//

#include "MuJoConverter.h"
#include <fstream>

MuJoConverter::MuJoConverter(std::string input, std::string output, std::string keyPath) {
  m_in = input;
  m_out = output;
  m_keyPath = keyPath;
}

MuJoConverter::~MuJoConverter() {
  // deallocated everything
  if (m_model) {
    mj_deleteModel(m_model);
  }

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

bool MuJoConverter::LoadModel() {
  m_model = mj_loadXML(m_in.c_str(), 0, m_err, 1000);

  if (!m_model) {
    std::cout << m_err << std::endl;
    return false;
  }

  return true;
}

bool MuJoConverter::SaveModel() {
  std::ifstream inoutfile;
  inoutfile.open(m_out.c_str(), std::ios_base::in);
  if (inoutfile.is_open()) {
    std::cout << "Output file already exists" << std::endl;
    inoutfile.close();
    return false;
  }

  if (mj_saveLastXML(m_out.c_str(), m_model, m_err, 1000)) {
    std::cout << m_err << std::endl;
    return false;
  }

  return true;
}