#include <matrix.h>

matrix	*new_matrix_glspec() {
	matrix	*self;

	self = (matrix *)malloc(sizeof(matrix));
	if (!self) {
		char *tmp = "new_matrix: error: ";
		char *tmp2 = strerror(ENOMEM);
		write(2, tmp, strlen(tmp));
		write(2, tmp2, strlen(tmp2));
		write(2, "\n", 1);
		exit (-1);
	}
	matrix_ctr_glspec(&self);
	return self;
}