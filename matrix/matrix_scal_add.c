#include <matrix.h>

void	matrix_scal_add(matrix **self, float that) {
	int size;
	int i = -1;

	if (!self || !*self) {
		char *err = "matrix_add: error: target matrix doesn't exit!\n";
		write(2, err, strlen(err));
		return ;
	}
	size = (*self)->rows * (*self)->columns;
	while(++i < size)
		(*self)->data[i] += that;
}