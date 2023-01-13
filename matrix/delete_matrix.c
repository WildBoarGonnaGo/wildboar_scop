#include <matrix.h>

void	delete_matrix(matrix **self) {
	if (!self || !*self) {
		char *err = "delete_matrix: error: memory is not allocated!\n";
		write(2, err, strlen(err));
		exit (-1);
	}
	matrix_dtr(self);
	free(*self);
	*self = NULL;
}