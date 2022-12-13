#include <matrix.h>

void matrix_rev_z(matrix** self, float radians) {
	matrix *tmp;

	tmp = new_matrix_2(4, 4);
	tmp->data[15] = 1;
	tmp->data[0] = cos(radians);
	tmp->data[1] = -sin(radians);
	tmp->data[4] = sin(radians);
	tmp->data[5] = cos(radians);
	tmp->data[10] = 1;
	matrix_multi(self, tmp);
	delete_matrix(&tmp);
}
