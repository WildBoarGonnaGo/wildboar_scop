 # **************************************************************************** #
 #                                                                              #
 #                                                         :::      ::::::::    #
 #    Makefile                                           :+:      :+:    :+:    #
 #                                                     +:+ +:+         +:+      #
 #    By: lchantel <lchantel@student.42.fr>          +#+  +:+       +#+         #
 #                                                 +#+#+#+#+#+   +#+            #
 #    Created: 2022/09/16 16:59:54 by lchantel          #+#    #+#              #
 #    Updated: 2023/01/13 02:34:53 by                  ###   ########.fr        #
 #                                                                              #
 # **************************************************************************** #

 EXEC_FILE = scop
 LIB = ./libft/libft.a

 SRC =	bmp_process/bmp_proc_ctor.c \
 		bmp_process/bmp_proc_dtor.c \
 		bmp_process/delete_bmpProc.c \
 		bmp_process/new_bmpProc.c \
 		matrix/delete_matrix.c \
 		matrix/matrix_add.c \
 		matrix/matrix_ctr.c \
        matrix/matrix_ctr_2.c \
 		matrix/matrix_dtr.c \
        matrix/matrix_multi.c \
        matrix/matrix_scal_add.c \
        matrix/matrix_scal_multi.c \
        matrix/new_matrix.c \
        matrix/new_matrix_2.c \
 		matrix/matrix_rev_x.c \
 		matrix/matrix_rev_y.c \
        matrix/matrix_rev_z.c \
        matrix/matrix_trans.c \
        matrix/matrix_scale.c \
        matrix/matrix_perspective.c \
        matrix/matrix_perspective_ret.c \
        matrix/matrix_multi_rev.c \
        matrix/matrix_multi_rev_ret.c \
        matrix/matrix_ctr_glspec.c \
        matrix/new_matrix_glspec.c \
        wavefront_obj_loader/delete_wavefront_obj_loader.c \
        wavefront_obj_loader/new_wavefront_obj_loader.c \
        wavefront_obj_loader/wavefront_obj_loader_ctr.c \
        wavefront_obj_loader/wavefront_obj_loader_dtr.c \
        glad/src/glad.c

CC = clang
OBJ = $(SRC:.c=.o)
INCLUDES =	-I glad/include -I bmp_process -I matrix \
			-I wavefront_obj_loader -I libft -I /opt/homebrew/Cellar/glfw/3.3.8/include/
LIBS = -L/opt/homebrew/lib -lglfw -lm -L libft -lft -framework Cocoa -framework OpenGL

$(EXEC_FILE):	$(LIB)	$(OBJ)
	@echo "Every funtion is compile proved ..."
	@echo "Making program executable ..."
	@$(CC) ./main.c -o $(EXEC_FILE) $(OBJ) $(INCLUDES) $(LIBS)

$(LIB):
	@echo "Building libft static library ..."
	@make all bonus -C ./libft
	@echo "All functions added to static lib ..."

$(OBJ): %.o :%.c
	@echo "Check $< to be right ..."
	@$(CC) -o $@ -c $< $(INCLUDES)

all: $(EXEC_FILE)

clean:
	@echo "removing all side binaries..."
	@rm -f $(OBJS)
	@rm -f matrix/*.o
	@rm -f glad/src/glad.o
	@rm -f bmp_process/*.o
	@rm -f wavefront_obj_loader/*.o
	@make clean -C ./libft

fclean: clean
	@echo "removing 'scop' binary..."
	@rm -f $(EXEC_FILE)
	@echo "removing libft..."
	@make fclean -C ./libft

re: fclean all
