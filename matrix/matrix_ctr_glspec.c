#include <matrix.h>

void	matrix_ctr_glspec(matrix **self) {
	int i = -1;

	(*self)->rows = 4;
	(*self)->columns = 4;
	(*self)->data = (float *)malloc(sizeof(float) * 16);
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
	while (++i < 15)
		(*self)->data[i] = 0;
	(*self)->data[0] = 1.0f;
	(*self)->data[5] = 1.0f;
	(*self)->data[10] = 1.0f;
	(*self)->data[15] = 1.0f;
}