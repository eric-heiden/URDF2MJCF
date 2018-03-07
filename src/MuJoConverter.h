//
// Created by hjzh on 18-3-2.
//

#ifndef MUJOCONV_MUJOCONVERTER_H
#define MUJOCONV_MUJOCONVERTER_H

#include "MJModel.h"
#include <string>
#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

enum FileType {
  FILE_UNKNOWN = 0,
  FILE_XML,
  FILE_URDF,
};

class MuJoConverter {
public:
  MuJoConverter(std::string input, std::string output, std::string keyPath);

  virtual ~MuJoConverter();

  bool Init();

  bool Convert();

private:
  MJModel m_model;
  std::string m_keyPath;
  std::string m_in;
  std::string m_out;

  char m_err[1000];

  inline FileType filetype(std::string file_path);

  bool LoadModel();

  bool SaveModel();

  bool AddLightToMJCF(rapidxml::xml_document<>& doc, char *light_data, char *ground_data);
};

#endif //MUJOCONV_MUJOCONVERTER_H
