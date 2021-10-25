cmake_minimum_required(VERSION 3.7.2)
project(wildboar_scop C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER clang)
add_compile_options(-g)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(${PROJECT_NAME} train/glfw_icosahedron3d.c)
    message("You're on MacOS X")
    find_package(OpenGL REQUIRED)

    include_directories(${OPENGL_INCLUDE_DIRS} "/opt/homebrew/include/")
    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} -L"/opt/homebrew/Cellar/glfw/3.3.4/lib/" -lglfw
            -L"/opt/homebrew/Cellar/glew/2.2.0_1/lib/" -lGLEW)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_executable(${PROJECT_NAME} train/icosahedron_3d.c)
    message("You're on Linux")
    target_link_libraries(${PROJECT_NAME} -lglut -lGLU -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm)
else()
    message("OS is not detected")
endif()