//
// Created by hjzh on 18-3-6.
//

#ifndef MUJOCONV_MJMODEL_H
#define MUJOCONV_MJMODEL_H

#include "mujoco.h"
#include <string>

class MJModel {
public:
  MJModel();
  virtual ~MJModel();

public:
  int Load(const std::string& in_file_path);
  int Save(const std::string& out_file_path);

private:
  mjModel *m_model = nullptr;
};
#endif //MUJOCONV_MJMODEL_H
