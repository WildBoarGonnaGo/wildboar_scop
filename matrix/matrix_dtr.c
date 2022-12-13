#include <matrix.h>

void	matrix_dtr(matrix **self) {
	if (!(*self)->data) {
		char *err = "matrix_dtr: error: memory is not allocated!\n";
		write(2, err, strlen(err));
		free(*self);
		*self = NULL;
		exit -1;
	}
	free((*self)->data);
}