#include <wavefront_obj_loader.h>

void 	delete_wavefront_obj_loader(wavefront_obj_loader **self) {
	if (!self || !*self) {
		char *err = "delete_wavefront_obj_loader: error: null pointer";

		write(2, err, strlen(err));
		write(2, "\n", 1);
		exit (-1);
	}
	wavefront_obj_loader_dtr(self);
	free(*self);
	*self = NULL;
}