#include <wavefront_obj_loader.h>
#include <time.h>
#include <float.h>

/*
 typedef struct _wavefront_obj_loader {
	GLfloat 		*verticies;
	GLint			*indicies;
	unsigned int	vert_size;
	unsigned int	vert_capacity;
	unsigned int	elem_size;
	unsigned int	elem_capacity;
 	char			*title;
 	GLfloat			xy_bound[4];
}	wavefront_obj_loader;
 * */

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

void	elem_preview(wavefront_obj_loader **self, char *line) {
	char	**line_split;
	int 	size = -1;
	int 	indicies[4] = {0};

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
		(*self)->verticies[(indicies[0] - 1) * 8 + 6] = 0.0f;
		(*self)->verticies[(indicies[0] - 1) * 8 + 7] = 0.0f;
		(*self)->verticies[(indicies[1] - 1) * 8 + 6] = 1.0f;
		(*self)->verticies[(indicies[1] - 1) * 8 + 7] = 0.0f;
		(*self)->verticies[(indicies[2] - 1) * 8 + 6] = 1.0f;
		(*self)->verticies[(indicies[2] - 1) * 8 + 7] = 1.0f;
	}
	if (size == 5) {
		indicies[0] = ft_atoi(line_split[1]);
		indicies[1] = ft_atoi(line_split[2]);
		indicies[2] = ft_atoi(line_split[3]);
		indicies[3] = ft_atoi(line_split[4]);
		while ((*self)->elem_size + 6 >= (*self)->elem_capacity) { indicies_realloc(self); }

		(*self)->indicies[(*self)->elem_size++] = indicies[0];
		(*self)->indicies[(*self)->elem_size++] = indicies[1];
		(*self)->indicies[(*self)->elem_size++] = indicies[2];
		(*self)->indicies[(*self)->elem_size++] = indicies[2];
		(*self)->indicies[(*self)->elem_size++] = indicies[3];
		(*self)->indicies[(*self)->elem_size++] = indicies[0];
		(*self)->verticies[(indicies[0] - 1) * 8 + 6] = 0.0f;
		(*self)->verticies[(indicies[0] - 1) * 8 + 7] = 0.0f;
		(*self)->verticies[(indicies[1] - 1) * 8 + 6] = 1.0f;
		(*self)->verticies[(indicies[1] - 1) * 8 + 7] = 0.0f;
		(*self)->verticies[(indicies[2] - 1) * 8 + 6] = 1.0f;
		(*self)->verticies[(indicies[2] - 1) * 8 + 7] = 1.0f;
		(*self)->verticies[(indicies[3] - 1) * 8 + 6] = 0.0f;
		(*self)->verticies[(indicies[3] - 1) * 8 + 7] = 1.0f;
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
		(*self)->vert_size += 2;
		for (int i = 0; i < 3; ++i)
			(*self)->verticies[++(*self)->vert_size] = rand() % 256;
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

		write(2, err, strlen(err));
		write(2, err2, strlen(err2));
		write(2, "\n", 1);
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
	srand(time(NULL));
	while ((getline(&line, &linecapp, fd)) > 0) {
		line_review(self, line);
		free(line);
		line = NULL;
	}
}