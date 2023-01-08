#include <wavefront_obj_loader.h>

/*
typedef struct _wavefront_obj_loader {
	GLfloat 		*verticies;
	GLint			*indicies;
	unsigned int	vert_size;
	unsigned int	vert_capacity;
	unsigned int	elem_size;
	unsigned int	elem_capacity;
	char			*title;
}	wavefront_obj_loader;
*/

void	wavefront_obj_loader_dtr(wavefront_obj_loader **self) {
	if ((*self)->verticies) {
		free((*self)->verticies);
		(*self)->verticies = NULL;
	}
	if ((*self)->indicies) {
		free((*self)->indicies);
		(*self)->indicies = NULL;
	}
	if ((*self)->title) {
		free((*self)->title);
		(*self)->title = NULL;
	}
}