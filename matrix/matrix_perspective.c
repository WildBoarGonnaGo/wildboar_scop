/*t_mat *mat_perspective(float angle, float ratio,
					   float near, float far) {
	t_mat *to_return;
	float tan_half_angle;

	to_return = mat_new(4, 4);
	mat_zero(to_return);
	tan_half_angle = tan(angle / 2);
	mat_set(to_return, 1, 1, 1 / (ratio * tan_half_angle));
	mat_set(to_return, 2, 2, 1 / (tan_half_angle));
	mat_set(to_return, 3, 3, -(far + near) / (far - near));
	mat_set(to_return, 4, 3, -1);
	mat_set(to_return, 3, 4, -(2 * far * near) / (far - near));
	return (to_return);
}*/

#include <matrix.h>

void	matrix_perspective(matrix **self, float rad,
						   float ratio, float near, float far) {
	matrix	*tmp;
	float	half_angle;

	tmp = new_matrix_2(4, 4);
	half_angle = tanf(rad / 2);
	tmp->data[0] = 1.0f / (ratio * half_angle);
	tmp->data[5] = 1.0f / half_angle;
	tmp->data[10] = -1.0f * (far + near) / (far - near);
	tmp->data[11] = -2.0f * far * near / (far - near);
	tmp->data[14] = -1.0f;
	matrix_multi(self, tmp);
	delete_matrix(&tmp);
}

