#include <matrix.h>

matrix	*matrix_perspective_ret(float rad, float ratio, float near, float far) {
	matrix	*tmp;
	float	half_angle;

	tmp = new_matrix_2(4, 4);
	half_angle = tanf(rad / 2);
	tmp->data[0] = 1.0f / (ratio * half_angle);
	tmp->data[5] = 1.0f / half_angle;
	tmp->data[10] = -1.0f * (far + near) / (far - near);
	tmp->data[11] = -2.0f * far * near / (far - near);
	tmp->data[14] = -1.0f;
	return tmp;
}