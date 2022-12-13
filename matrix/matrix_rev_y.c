#include <matrix.h>

void matrix_rev_y(matrix** self, float radians) {
	matrix *tmp;

	tmp = new_matrix_2(4, 4);
	tmp->data[15] = 1;
	tmp->data[0] = cos(radians);
	tmp->data[2] = sin(radians);
	tmp->data[5] = 1;
	tmp->data[8] = -1 * sin(radians);
	tmp->data[10] = cos(radians);
	matrix_multi(self, tmp);
	delete_matrix(&tmp);
}
