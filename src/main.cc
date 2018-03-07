/// This project is used to convert URDF file to MuJoCo's MJCF file.
/// The pipeline of this project is as following:
/// TODO preprocess the urdf file, change DAE to STL, stl to STL, dae to STL
/// 2. mj_LoadXML
/// 3. insert camera, motors
/// 4. Save model to MJCF file

#include <iostream>
#include "MuJoConverter.h"

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cout << "Usage: MuJoCoverter <input filename> <output filename> <key_path>" << std::endl;
    return -1;
  }

  MuJoConverter muJoConverter(argv[1], argv[2], argv[3]);

  if (!muJoConverter.Init()) {
    std::cout << "muJoConverter failed to initialize check your filetypes and MuJoCo key" << std::endl;
    return -2;
  }

  if (!muJoConverter.LoadModel()) {
    std::cout << "muJoConverter failed to load model from input file" << std::endl;
    return -3;
  }

  /// TODO
  muJoConverter.SetDefaultCam();

  muJoConverter.SaveModel();

  return 0;
}