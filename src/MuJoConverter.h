//
// Created by hjzh on 18-3-2.
//

#ifndef MUJOCONV_MUJOCONVERTER_H
#define MUJOCONV_MUJOCONVERTER_H

#include "mujoco.h"

#include <string>
#include <iostream>

enum FileType {
  FILE_UNKNOWN = 0,
  FILE_XML,
  FILE_URDF,
};

class MuJoConverter {
public:
  MuJoConverter(std::string input, std::string output, std::string keyPath);

  virtual ~MuJoConverter();

  bool SaveModel();

  bool Init();

  bool LoadModel();

  void SetDefaultCam();

private:
  mjModel* m_model = nullptr;
  std::string m_keyPath;
  std::string m_in;
  std::string m_out;

  char m_err[1000];

  inline FileType filetype(std::string file_path);
};

#endif //MUJOCONV_MUJOCONVERTER_H
