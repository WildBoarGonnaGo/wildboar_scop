#include <matrix.h>

matrix	*new_matrix_2(int row, int column) {
	matrix	*self;

	self = (matrix *)malloc(sizeof(matrix));
	if (!self) {
		char *tmp = "new_matrix_2: error: ";
		char *tmp2 = strerror(errno);
		write(2, tmp, strlen(tmp));
		write(2, tmp2, strlen(tmp2));
		write(2, "\n", 1);
		exit (-1);
	}
	matrix_ctr_2(&self, row, column);
	return self;
}