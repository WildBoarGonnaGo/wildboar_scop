#include <matrix.h>

void matrix_rev_z(matrix** self, float radians) {
	matrix *tmp;

	if (!self || !*self) {
		char *err = "matrix_add: error: target matrix doesn't exit!\n";
		write(2, err, strlen(err));
		return ;
	}
	tmp = new_matrix_glspec();
	tmp->data[0] = cos(radians);
	tmp->data[1] = -sin(radians);
	tmp->data[4] = sin(radians);
	tmp->data[5] = cos(radians);
	matrix_multi(self, tmp);
	delete_matrix(&tmp);
}
