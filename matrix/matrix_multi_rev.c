#include <matrix.h>

/*
| cos(alpha) + Rx^2 * (1 - cos(alpha))			Rx * Ry * (1 - cos(alpha)) - Rz * sin(alpha)	Rx * Rz * (1 - cos(alpha)) + Ry * sin(alpha)	0 |
| Ry * Rx * (1 - cos(alpha)) + Rz * sin(alpha)	cos(alpha) + Ry^2 * (1 - cos(alpha))			Ry * Rz * (1 - cos(alpha)) - Rx * sin(alpha)	0 |
| Rz * Rx * (1 - cos(alpha)) - Ry * sin(alpha)	Rz * Ry * (1 - cos(alpha)) + Rx * sin(alpha)	cos(alpha) + Rz^2 * (1 - cos(alpha))			0 |
| 0												0												0												1 |
 * */

void	matrix_multi_rev(matrix **self, float rad, float *fact) {
	matrix	*mat4;
	float	Rx, Ry, Rz, cos_alpha, sin_alpha;

	if (!fact) {
		char	*err = "matrix_multi_rev: error: fact variable is nullptr\n";
		write(2, err, strlen(err));
		return ;
	}
	Rx = fact[0]; Ry = fact[1]; Rz = fact[2];
	cos_alpha = cosf(rad); sin_alpha = sinf(rad);
	mat4 = new_matrix_glspec();
	mat4->data[0] = cos_alpha + Rx * Rx * (1 - cos_alpha);
	mat4->data[1] = Rx * Ry * (1 - cos_alpha) - Rz * sin_alpha;
	mat4->data[2] = Rx * Rz * (1 - cos_alpha) + Ry * sin_alpha;
	mat4->data[4] = Ry * Rx * (1 - cos_alpha) + Rz * sin_alpha;
	mat4->data[5] = cos_alpha + Ry * Ry * (1 - cos_alpha);
	mat4->data[6] = Ry * Rz * (1 - cos_alpha) - Rx * sin_alpha;
	mat4->data[8] = Rz * Rx * (1 - cos_alpha) - Ry * sin_alpha;
	mat4->data[9] = Rz * Ry * (1 - cos_alpha) + Rx * sin_alpha;
	mat4->data[10] = cos_alpha + Rz * Rz * (1 - cos_alpha);
	matrix_multi(self, mat4);
	delete_matrix(&mat4);
}