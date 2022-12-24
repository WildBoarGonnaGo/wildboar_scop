#include <matrix.h>

void	matrix_trans(matrix **self, float *data) {
	matrix	*tmp;

	if (!self || !*self) {
		char *err = "matrix_add: error: target matrix doesn't exit!\n";
		write(2, err, strlen(err));
		return ;
	}
	tmp = new_matrix_glspec();
	tmp->data[3] = data[0];
	tmp->data[7] = data[1];
	tmp->data[11] = data[2];
	matrix_multi(self, tmp);
	delete_matrix(&tmp);
}