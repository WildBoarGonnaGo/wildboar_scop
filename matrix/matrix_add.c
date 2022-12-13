#include <matrix.h>

void	matrix_add(matrix **self, const matrix *that) {
	int size;
	int i = -1;

	if (!self || !*self || !that) {
		char *err = "matrix_add: error: one of the matricies doesn't exist!\n";
		write(2, err, strlen(err));
		return ;
	}
	if ((*self)->rows != that->rows || (*self)->columns != that->columns) {
		char *err = "matrix_add: error: can't add one matrix to another!\n";
		write(2, err, strlen(err));
		return ;
	}
	size = that->rows * that->columns;
	while (++i < size)
		(*self)->data[i] += that->data[i];
}