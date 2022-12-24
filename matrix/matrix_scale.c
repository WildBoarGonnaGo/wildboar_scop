#include <matrix.h>

void	matrix_scale(matrix **self, float *data) {
	matrix	*tmp;

	if (!self || !*self) {
		char *err = "matrix_add: error: target matrix doesn't exit!\n";
		write(2, err, strlen(err));
		return ;
	}
	tmp = new_matrix_glspec();
	tmp->data[0] = data[0];
	tmp->data[5] = data[1];
	tmp->data[10] = data[2];
	matrix_multi(self, tmp);
	delete_matrix(&tmp);
}