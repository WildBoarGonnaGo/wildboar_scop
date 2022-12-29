cmake_minimum_required(VERSION 3.7.2)
project(wildboar_scop C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER clang)
# set_source_files_properties(./glad/src/glad.c PROPERTIES LANGUAGE CXX )
add_compile_options(-g)

# add_executable(${PROJECT_NAME} ./train/glfw_tri_palete.c ./glad/src/glad.c)
add_executable(${PROJECT_NAME} ./bmp_process/bmp_proc_ctor.c
        bmp_process/bmp_proc_dtor.c
        bmp_process/delete_bmpProc.c
        bmp_process/new_bmpProc.c
        matrix/delete_matrix.c
        matrix/matrix_add.c
        matrix/matrix_ctr.c
        matrix/matrix_ctr_2.c
        matrix/matrix_dtr.c
        matrix/matrix_multi.c
        matrix/matrix_scal_add.c
        matrix/matrix_scal_multi.c
#        matrix/matrix_test.c
        matrix/new_matrix.c
        matrix/new_matrix_2.c
		matrix/matrix_rev_x.c
		matrix/matrix_rev_y.c
		matrix/matrix_rev_z.c
		matrix/matrix_trans.c
		matrix/matrix_scale.c
		matrix/matrix_perspective.c
		matrix/matrix_perspective_ret.c
		matrix/matrix_multi_rev.c
		matrix/matrix_multi_rev_ret.c
#        train/glfw_texture_sample.c
		matrix/matrix_ctr_glspec.c
		matrix/new_matrix_glspec.c
#		train/glfw_matrix_transform.c
#		train/glfw_view_transform.c
		train/glfw_rotating_cube.c
        glad/src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC ./glad/include/)
target_include_directories(${PROJECT_NAME} PUBLIC /opt/homebrew/Cellar/glfw/3.3.8/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ./bmp_process)
target_include_directories(${PROJECT_NAME} PUBLIC ./matrix)
target_link_directories(${PROJECT_NAME} PUBLIC "/opt/homebrew/lib")
target_link_libraries(${PROJECT_NAME} PUBLIC -lglfw -lm)
target_link_libraries(${PROJECT_NAME} PUBLIC "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} PUBLIC "-framework OpenGL")

#if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#   add_executable(${PROJECT_NAME} train/glfw_icosahedron3d.c)
#    add_executable(${PROJECT_NAME} train/glfw_funny_face.c)
#    message("You're on MacOS X")
#    find_package(OpenGL REQUIRED)

#    include_directories(${OPENGL_INCLUDE_DIRS} "/opt/homebrew/include/")
#    target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} -L"/opt/homebrew/lib/" -lglfw
#            -L"/opt/homebrew/lib/" -lGLEW -lm)
#elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#    add_executable(${PROJECT_NAME} train/glfw_funny_face.c)
#    message("You're on Linux")
#    target_link_libraries(${PROJECT_NAME} -lglut -lGLU -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm)
#else()
#    message("OS is not detected")
#endif()
