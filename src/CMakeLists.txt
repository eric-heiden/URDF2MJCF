include_directories(/home/hjzh/.mujoco/mjpro150/include ../rapidxml)

link_directories(/home/hjzh/.mujoco/mjpro150/bin /usr/lib/x86_64-linux-gnu)

add_executable(MuJoConv main.cc MuJoConverter.cc MJModel.cc MJModel.h ../rapidxml/rapidxml.hpp ../rapidxml/rapidxml_print.hpp)

target_link_libraries(MuJoConv mujoco150 mujoco150nogl glew glewegl glewosmesa glfw glut GL GLU)
