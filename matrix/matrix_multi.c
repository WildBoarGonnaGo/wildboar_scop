#include <matrix.h>

float	matrix_multi_calc_elem(const matrix *self, const matrix *that,
							   const int row, const int column) {
	float res = 0;
	int i = -1;
	while (++i < self->columns) {
		res += self->data[self->columns * row + i]
				* that->data[i * that->columns + column];
	}
	return res;
}

void	matrix_multi(matrix **self, const matrix *that) {
	matrix *res = NULL;
	int i = -1, j;

	if (!self || !*self || !that) {
		char *err = "matrix_multi: error: one of the matricies doesn't exist!\n";
		write(2, err, strlen(err));
		return ;
	}
	if ((*self)->columns != that->rows) {
		char *err = "matrix_multi: error: left matrix colum size isn't not equal to the right matrix row size!\n";
		write(2, err, strlen(err));
		return ;
	}
	/*c_ij = a_i1 * b1j + a_i2 * b_2j + ... + a_in * b_nj*/
	res = new_matrix_2((*self)->rows, that->columns);
	while (++i < res->rows) {
		j = -1;
		while (++j < res->columns)
			res->data[i * res->columns + j] =
					matrix_multi_calc_elem(*self, that, i, j);
	}
	matrix_dtr(self);
	matrix_ctr(self, res->data, res->rows, res->columns);
	delete_matrix(&res);
}