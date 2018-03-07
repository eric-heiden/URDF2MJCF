//
// Created by hjzh on 18-3-6.
//

#include "MJModel.h"
#include <iostream>
#include <fstream>

int MJModel::Load(const std::string& in_file_path) {
  if (m_model) {
    std::cout << "has loaded the model" << std::endl;
    return -1;
  }

  char err[1000];
  m_model = mj_loadXML(in_file_path.c_str(), 0, err, 1000);

  if (!m_model) {
    /// TODO add logger
    std::cout << err << std::endl;
    return -2;
  }

  return 0;
}

int MJModel::Save(const std::string& out_file_path) {
//  std::ifstream inoutfile;
//  inoutfile.open(out_file_path.c_str(), std::ios_base::in);
//  if (inoutfile.is_open()) {
//    std::cout << "Output file already exists" << std::endl;
//    inoutfile.close();
//    return -1;
//  }

  char err[1000];
  /// Pay attention
  if (!mj_saveLastXML(out_file_path.c_str(), m_model, err, 1000)) {
    std::cout << err << std::endl;
    return -2;
  }

  return 0;
}

MJModel::~MJModel() {
  /// deallocated everything
  if (m_model) {
    mj_deleteModel(m_model);
  }
}

MJModel::MJModel() {

}