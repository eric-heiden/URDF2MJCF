#include <iostream>
#include "MuJoConverter.h"
//#include "tclap/CmdLine.h"
//
//void parseOptions(int argc, char **argv, CmdParam& param) {
//  try {
//
//  } catch (TCL)
//}

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

  muJoConverter.SaveModel();

  return 0;
}