cmake_minimum_required(VERSION 3.10)
project(TareaDosMallas)

set(CMAKE_CXX_STANDARD 11)

add_executable(TareaDosMallas main.cpp lepp.cpp lepp.h Face.cpp Face.h Vertex.cpp Vertex.h tests.h)
target_link_libraries(TareaDosMallas -lOpenGl32 -lfreeGLUT)