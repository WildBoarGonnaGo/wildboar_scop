#include <matrix.h>

void	matrix_ctr_2(matrix **self, int row, int column) {
	int size;
	int i = -1;

	(*self)->rows = row;
	(*self)->columns = column;
	(*self)->data = (float *)malloc(sizeof(float) * row * column);
	if (!(*self)->data) {
		char	*tmp = "matrix_ctr: error: ";
		char	*errmsg = strerror(ENOMEM);
		write(2, tmp, strlen(tmp));
		write(2, errmsg, strlen(errmsg));
		write(2, "\n", 1);
		free(*self);
		*self = NULL;
		exit -1;
	}
	size = row * column;
	while (++i < size)
		(*self)->data[i] = 0.0f;
}