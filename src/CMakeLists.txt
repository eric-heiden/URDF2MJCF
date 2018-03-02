include_directories(/home/hjzh/.mujoco/mjpro150/include)

link_directories(/home/hjzh/.mujoco/mjpro150/bin /usr/lib/x86_64-linux-gnu)

add_executable(MuJoConv main.cc MuJoConverter.cc)

target_link_libraries(MuJoConv mujoco150 mujoco150nogl glew glewegl glewosmesa glfw glut GL GLU)
