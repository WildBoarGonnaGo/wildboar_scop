#include <wavefront_obj_loader.h>
#include <time.h>
#include <float.h>

void	error_elem_size(wavefront_obj_loader **self, char *errstr) {
	char *err = "new_wavefront_obj_loader: error: ";

	ft_putstr_fd(err, 2);
	ft_putendl_fd(errstr, 2);
	wavefront_obj_loader_dtr(self);
	free(*self);
	*self = NULL;
	exit(-1);
}

void	error_vert_size(wavefront_obj_loader **self, char *errstr) {
	char *err = "new_wavefront_obj_loader: error: ";

	ft_putstr_fd(err, 2);
	ft_putendl_fd(errstr, 2);
	wavefront_obj_loader_dtr(self);
	free(*self);
	*self = NULL;
	exit (-1);
}

void	indicies_realloc(wavefront_obj_loader **self) {
	int 	elem_capacity = ((*self)->elem_capacity) ? (*self)->elem_capacity * 2 : 1;
	GLint	*indicies;

	indicies = (GLint *)malloc(sizeof(GLint) * elem_capacity);
	for (int i = 0; i < (*self)->elem_size; ++i)
		indicies[i] = (*self)->indicies[i];
	free((*self)->indicies);
	(*self)->elem_capacity = elem_capacity;
	(*self)->indicies = indicies;
}

void	verticies_realloc(wavefront_obj_loader **self) {
	int 	vert_capacity = ((*self)->vert_capacity) ? (*self)->vert_capacity * 2 : 1;
	GLfloat	*verticies;

	verticies = (GLfloat *)malloc(sizeof(GLfloat) * vert_capacity);
	for (int i = 0; i < (*self)->vert_size; ++i)
		verticies[i] = (*self)->verticies[i];
	free((*self)->verticies);
	(*self)->vert_capacity = vert_capacity;
	(*self)->verticies = verticies;
}

void	output_realloc(wavefront_obj_loader **self) {
	int 	output_capacity = ((*self)->output_capacity) ? (*self)->output_capacity * 2 : 1;
	GLfloat	*output;

	output = (GLfloat *)malloc(sizeof(GLfloat) * output_capacity);
	for (int i = 0; i < (*self)->output_size; ++i)
		output[i] = (*self)->output[i];
	if ((*self)->output) free((*self)->output);
	(*self)->output_capacity = output_capacity;
	(*self)->output = output;
}

void	elem_preview(wavefront_obj_loader **self, char *line) {
	char	**line_split;
	int 	size = -1;
	int 	indicies[4] = {0};
	GLfloat	color;

	if (!(*self)->vert_size) {
		free(line);
		line = NULL;
		error_vert_size(self, "no verticy is defined");
	}
	line_split = ft_split(line, ' ');
	while (line_split[++size]) ;
	if (size == 4) {
		indicies[0] = ft_atoi(line_split[1]);
		indicies[1] = ft_atoi(line_split[2]);
		indicies[2] = ft_atoi(line_split[3]);
		while ((*self)->elem_size + 3 >= (*self)->elem_capacity) { indicies_realloc(self); }

		(*self)->indicies[(*self)->elem_size++] = indicies[0];
		(*self)->indicies[(*self)->elem_size++] = indicies[1];
		(*self)->indicies[(*self)->elem_size++] = indicies[2];
		while ((*self)->output_size + 24 >= (*self)->output_capacity)
			output_realloc(self);

		color =  rand() % 256 / 255.0f;
		for (int i = 0; i < 3; ++i) {
			indicies[i] = (indicies[i] - 1) * 8;
			for (int j = 0; j < 3; ++j)
				(*self)->output[(*self)->output_size++] = (*self)->verticies[indicies[i] + j];
			for (int j = 3; j < 6; ++j)
				(*self)->output[(*self)->output_size++] = color;
			if (!i) { (*self)->output[(*self)->output_size++] = 0.0f; (*self)->output[(*self)->output_size++] = 0.0f; }
			else if (i == 1) { (*self)->output[(*self)->output_size++] = 1.0f; (*self)->output[(*self)->output_size++] = 0.0f; }
			else if (i == 2) { (*self)->output[(*self)->output_size++] = 1.0f; (*self)->output[(*self)->output_size++] = 1.0f; }
		}

	}
	if (size == 5) {
		GLint	quad_indicies[6] = {0};

		indicies[0] = ft_atoi(line_split[1]);
		indicies[1] = ft_atoi(line_split[2]);
		indicies[2] = ft_atoi(line_split[3]);
		indicies[3] = ft_atoi(line_split[4]);
		while ((*self)->elem_size + 6 >= (*self)->elem_capacity) { indicies_realloc(self); }

		quad_indicies[0] = indicies[0];
		quad_indicies[1] = indicies[1];
		quad_indicies[2] = indicies[2];
		quad_indicies[3] = indicies[2];
		quad_indicies[4] = indicies[3];
		quad_indicies[5] = indicies[0];

		for (int i = 0; i < 6; ++i)
			(*self)->indicies[(*self)->elem_size++] = quad_indicies[i];

		while ((*self)->output_size + 48 >= (*self)->output_capacity)
			output_realloc(self);
		for (int i = 0; i < 6; ++i) {
			if (!(i % 3)) color =  rand() % 256 / 255.0f;
			quad_indicies[i] = (quad_indicies[i] - 1) * 8;
			for (int j = 0; j < 3; ++j)
				(*self)->output[(*self)->output_size++] = (*self)->verticies[quad_indicies[i] + j];
			for (int j = 3; j < 6; ++j)
				(*self)->output[(*self)->output_size++] = color;
			if (!i || i == 5) { (*self)->output[(*self)->output_size++] = 0.0f; (*self)->output[(*self)->output_size++] = 0.0f; }
			else if (i == 1) { (*self)->output[(*self)->output_size++] = 1.0f; (*self)->output[(*self)->output_size++] = 0.0f; }
			else if (i == 2 || i == 3) { (*self)->output[(*self)->output_size++] = 1.0f; (*self)->output[(*self)->output_size++] = 1.0f; }
			else if (i == 4) { (*self)->output[(*self)->output_size++] = 0.0f; (*self)->output[(*self)->output_size++] = 1.0f; }
		}

	}
	if (size > 5 || size < 4) {
		for (int i = 0; line_split[i]; ++i) { free(line_split[i]); line_split[i] = NULL; }
		free(line_split);
		line_split = NULL;
		free(line);
		line = NULL;
		error_vert_size(self, "wrong number of element arguments");
	}
	for (int i = 0; line_split[i]; ++i) { free(line_split[i]); line_split[i] = NULL; }
	free(line_split);
	line_split = NULL;
}

void	line_review(wavefront_obj_loader **self, char *line) {
	char	tmp;
	char	tmp_title[128];

	bzero(tmp_title, 128);
	if (line[0] == 'v' && line[1] == ' ') {
		while ((*self)->vert_size + 8 >= (*self)->vert_capacity)
			verticies_realloc(self);

		char	**line_split = ft_split(line, ' ');
		int		number;
		for (number = 0; line_split[number]; ++number) ;
		if (number != 4) {
			for (int i = 0; line_split[i]; ++i) { free(line_split[i]); line_split[i] = NULL; }
			free(line_split);
			line_split = NULL;
			free(line);
			line = NULL;
			error_vert_size(self, "wrong number of verticy arguments");
		}

		sscanf(line, "%c %f %f %f", &tmp, &(*self)->verticies[(*self)->vert_size],
						&(*self)->verticies[(*self)->vert_size + 1],
						&(*self)->verticies[(*self)->vert_size + 2]);
		if ((*self)->verticies[(*self)->vert_size] < (*self)->xy_bound[0])
			(*self)->xy_bound[0] = (*self)->verticies[(*self)->vert_size];
		if ((*self)->verticies[(*self)->vert_size] > (*self)->xy_bound[1])
			(*self)->xy_bound[1] = (*self)->verticies[(*self)->vert_size];
		if ((*self)->verticies[(*self)->vert_size + 1] < (*self)->xy_bound[2])
			(*self)->xy_bound[2] = (*self)->verticies[(*self)->vert_size + 1];
		if ((*self)->verticies[(*self)->vert_size + 1] > (*self)->xy_bound[3])
			(*self)->xy_bound[3] = (*self)->verticies[(*self)->vert_size + 1];
		if ((*self)->verticies[(*self)->vert_size + 2] < (*self)->xy_bound[4])
			(*self)->xy_bound[4] = (*self)->verticies[(*self)->vert_size + 2];
		if ((*self)->verticies[(*self)->vert_size + 2] > (*self)->xy_bound[5])
			(*self)->xy_bound[5] = (*self)->verticies[(*self)->vert_size + 2];
		(*self)->vert_size += 2;
		for (int i = 0; i < 3; ++i)
			(*self)->verticies[++(*self)->vert_size] = 0;
		(*self)->verticies[++(*self)->vert_size] = -1.0f;
		(*self)->verticies[++(*self)->vert_size] = -1.0f;
		++(*self)->vert_size;
	}
	else if (line[0] == 'o' && line[1] == ' ') {
		if ((*self)->title) {
			free((*self)->title);
			(*self)->title = NULL;
		}
		sscanf(line, "%c %[^\n]s", &tmp, tmp_title);
		(*self)->title = ft_substr(tmp_title, 0, ft_strlen(tmp_title));
	}
	else if (line[0] == 'f' && line[1] == ' ')
		elem_preview(self, line);
}

void 	wavefront_obj_loader_ctr(wavefront_obj_loader **self, const char *file_abspath,
				 unsigned int vert_capacity, unsigned int elem_capacity) {
	FILE			*fd;
	unsigned long	linecapp = 128;
	char			*line;

	fd = fopen(file_abspath, "r");
	if (!fd) {
		char *err = "new_wavefront_obj_loader: error: ";
		char *err2 = strerror(errno);

		ft_putstr_fd(err, 2);
		ft_putendl_fd(err2, 2);
		free(*self);
		*self = NULL;
		exit (-1);
	}
	(*self)->verticies = (GLfloat *)malloc(sizeof(GLfloat) * vert_capacity);
	(*self)->vert_size = 0;
	(*self)->vert_capacity = vert_capacity;
	(*self)->indicies = (GLint *)malloc(sizeof(GLint) * elem_capacity);
	(*self)->elem_size = 0;
	(*self)->elem_capacity = elem_capacity;
	(*self)->title = NULL;
	(*self)->xy_bound[0] = FLT_MAX;
	(*self)->xy_bound[1] = FLT_MIN;
	(*self)->xy_bound[2] = FLT_MAX;
	(*self)->xy_bound[3] = FLT_MIN;
	(*self)->xy_bound[4] = FLT_MAX;
	(*self)->xy_bound[5] = FLT_MIN;
	(*self)->output_capacity = 0;
	(*self)->output_size = 0;
	(*self)->output = NULL;
	(*self)->texture = 0;
	srand(time(NULL));
	while ((getline(&line, &linecapp, fd)) > 0) {
		line_review(self, line);
		free(line);
		line = NULL;
	}
	if (!(*self)->elem_size)
		error_elem_size(self, "no face is defined");
	if (!(*self)->vert_size)
		error_vert_size(self, "no verticy is defined");
	if (!(*self)->title) (*self)->title = ft_strdup("Default");
}