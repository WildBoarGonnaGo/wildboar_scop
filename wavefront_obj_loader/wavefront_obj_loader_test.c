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

int main(void) {
	char	*filename = "../models/resources/42.obj";
	wavefront_obj_loader *test = *new_wavefront_obj_loader(filename, 512, 512);
	printf("verticies info:\n");
	for (int i = 0; i < test->vert_size; ++i)
		printf("%f%c", test->verticies[i], (i % 8) ? ' ' : '\n');
	printf("\nelements info")
	for (int i = 0; i < test->elem_size; ++i)
		printf("%f%c", test->indicies[i], (i % 3) ? ' ' : '\n');
	delete_wafefront_obj_loader(&test);
}