#include <wavefront_obj_loader.h>

wavefront_obj_loader	*new_wavefront_obj_loader(const char *file_abspath, unsigned int vert_capacity,
							  unsigned int elem_capacity) {
	wavefront_obj_loader *self;

	self = (wavefront_obj_loader *)malloc(sizeof(wavefront_obj_loader));
	if (!self) {
		char *err = "new_wavefront_obj_loader: error: ";
		char *err2 = strerror(errno);

		write(2, err, strlen(err));
		write(2, err2, strlen(err2));
		write(2, "\n", 1);
		exit (-1);
	}
	wavefront_obj_loader_ctr(&self, file_abspath, vert_capacity, elem_capacity);
	return self;
}