#ifndef WAVEFRONT_OBJ_LOADER_H
# define WAVEFRONT_OBJ_LOADER_H
# include <stdio.h>
# include <fcntl.h>
# include <glad/glad.h>

typedef struct _vertex_data_list {
	GLfloat data[8];
	struct _vertex_data_list *next;
} vertex_data_list;

typedef struct _wavefront_obj_loader {
	GLfloat *data;
	unsigned int size;
	unsigned int capacity;
	vertex_data_list *node;
} wavefront_obj_loader;

wavefront_obj_loader *new_wavefront_obj_loader(const char *file_abspath, unsigned int size);
void wavefront_obj_loader_ctr(wavefront_obj_loader **self, const char *file_abspath, unsigned int size);
void delete_wavefront_obj_loader(wavefront_obj_loader **self);

#endif
