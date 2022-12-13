#include <matrix.h>

int main(void) {
	matrix *a, *b, *c, *d;
	float c_data[] = {4.0f, 2.0f, 0.0f, 0.0f, 8.0f, 1.0f, 0.0f, 1.0f, 0.0f};
	float d_data[] = { 4.0f, 2.0f, 1.0f, 2.0f, 0.0f, 4.0f, 9.0f, 4.0f, 2.0f };

	a = new_matrix_2(2, 2);
	b = new_matrix_2(2, 2);

	for (int i = 0; i < 4; ++i) {
		a->data[i] = i + 1;
		b->data[i] = i + 5;
	}
	printf("matrix 'a':\n");
	for (int i = 0; i < 4; ++i)
		printf("%f%c", a->data[i], (i % 2) ? '\n' : ' ');
	printf("matrix 'b':\n");
	for(int i = 0; i < 4; ++i)
		printf("%f%c", b->data[i], (i % 2) ? '\n' : ' ');
	printf("result of matrix multiplication 'a x b':\n");
	matrix_multi(&a, b);
	for (int i = 0; i < 4; ++i)
		printf("%f%c", a->data[i], (i % 2) ? '\n' : ' ');
	delete_matrix(&a);
	delete_matrix(&b);
	c = new_matrix(c_data, 3, 3);
	d = new_matrix(d_data, 3, 3);
	printf("matrix 'c':\n");
	for (int i = 0; i < 9; ++i)
		printf("%f%c", c->data[i], (!((i + 1) % 3)) ? '\n' : ' ');
	printf("matrix 'd':\n");
	for(int i = 0; i < 9; ++i)
		printf("%f%c", d->data[i], (!((i + 1) % 3)) ? '\n' : ' ');
	matrix_multi(&c, d);
	printf("result of matrix multiplication 'c x d':\n");
	for (int i = 0; i < 9; ++i)
		printf("%f%c", c->data[i], (!((i + 1) % 3)) ? '\n' : ' ');
	delete_matrix(&c);
	delete_matrix(&d);
	return 0;
}