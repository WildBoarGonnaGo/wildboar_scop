#include <matrix.h>

void	matrix_ctr_2(matrix **self, int row, int column) {
	int size;
	int i = -1;

	(*self)->rows = row;
	(*self)->columns = column;
	(*self)->data = (float *)malloc(sizeof(float) * row * column);
	size = row * column;
	while (++i < size)
		(*self)->data[i] = 0;
}