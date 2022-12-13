#include <matrix.h>

void matrix_rev_x(matrix** self, float radians) {
	matrix *tmp;

	tmp = new_matrix_2(4, 4);
	tmp->data[15] = 1;
	tmp->data[0] = 1;
	tmp->data[5] = cos(radians);
	tmp->data[6] = -1 * sin(radians);
	tmp->data[9] = sin(radians);
	tmp->data[10] = cos(radians);
	matrix_multi(self, tmp);
	delete_matrix(&tmp);
}
