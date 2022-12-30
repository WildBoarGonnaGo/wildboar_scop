#ifndef WAVEFRONT_OBJ_LOADER_H
# define WAVEFRONT_OBJ_LOADER_H
# include <stdio.h>
# include <fcntl.h>
# include <glad/glad.h>
# include <string.h>
# include <errno.h>
# include <libft.h>
# include <stdlib.h>

typedef struct _wavefront_obj_loader {
	GLfloat 		*verticies;
	GLint			*indicies;
	unsigned int	vert_size;
	unsigned int	vert_capacity;
	unsigned int	elem_size;
	unsigned int	elem_capacity;
	char			*title;
}	wavefront_obj_loader;

wavefront_obj_loader	*new_wavefront_obj_loader(const char *file_abspath, unsigned int vert_capacity,
												  unsigned int elem_capacity);
void 					wavefront_obj_loader_ctr(wavefront_obj_loader **self, const char *file_abspath,
												  unsigned int vert_capacity, unsigned int elem_capacity);
void 					delete_wavefront_obj_loader(wavefront_obj_loader **self);
void					wavefront_obj_loader_dtr(wavefront_obj_loader **self);

#endif
