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
		matrix/matrix_ctr_glspec.c
		matrix/new_matrix_glspec.c
		wavefront_obj_loader/delete_wavefront_obj_loader.c
		wavefront_obj_loader/new_wavefront_obj_loader.c
		wavefront_obj_loader/wavefront_obj_loader_ctr.c
		wavefront_obj_loader/wavefront_obj_loader_dtr.c
		main.c
        glad/src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC ./glad/include/)
target_include_directories(${PROJECT_NAME} PUBLIC /opt/homebrew/Cellar/glfw/3.3.8/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ./bmp_process)
target_include_directories(${PROJECT_NAME} PUBLIC ./matrix)
target_include_directories(${PROJECT_NAME} PUBLIC ./wavefront_obj_loader)
target_include_directories(${PROJECT_NAME} PUBLIC ./libft)
target_link_directories(${PROJECT_NAME} PUBLIC "/opt/homebrew/lib")
target_link_directories(${PROJECT_NAME} PUBLIC ./libft)
target_link_libraries(${PROJECT_NAME} PUBLIC -lglfw -lm -lft)
target_link_libraries(${PROJECT_NAME} PUBLIC "-framework Cocoa")
target_link_libraries(${PROJECT_NAME} PUBLIC "-framework OpenGL")