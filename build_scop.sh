#!/bin/bash

g++ -g train/gflw_exc_2vao_2vbo.cpp ./glad/src/glad.c -I/opt/homebrew/Cellar/glfw/3.3.8/include/  -I./glad/include \
  -L/opt/homebrew/lib -lglfw -framework OpenGL -framework Cocoa -o test