#ifndef MATRIX_H
# define MATRIX_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>

typedef struct _list {
	void			*data;
	struct _list	*next;
} list;

typedef struct _matrix {
	int 	rows;
	int		columns;
	float 	*data;
}	matrix;

matrix	*new_matrix(float *data, int row, int column);
matrix	*new_matrix_2(int row, int column);
matrix	*new_matrix_glspec();
void	matrix_ctr(matrix **self, float *data, int row, int column);
void	matrix_ctr_2(matrix **self, int row, int column);
void	matrix_ctr_glspec(matrix **self);
void	delete_matrix(matrix **self);
void	matrix_dtr(matrix **self);
void	matrix_scal_add(matrix **self, float that);
void	matrix_scal_multi(matrix **self, float that);
void	matrix_add(matrix **self, const matrix *that);
void	matrix_multi(matrix **self, const matrix *that);
void	matrix_rev_x(matrix **self, float radians);
void	matrix_rev_y(matrix **self, float radians);
void	matrix_rev_z(matrix **self, float radians);
void	matrix_scale(matrix **self, float *data);
void	matrix_trans(matrix **self, float *data);

#endif
