#include <wavefront_obj_loader.h>
#include <time.h>

/*
 typedef struct _wavefront_obj_loader {
	GLfloat 		*verticies;
	GLint			*indicies;
	unsigned int	vert_size;
	unsigned int	vert_capacity;
	unsigned int	elem_size;
	unsigned int	elem_capacity;
 	char			*title;
}	wavefront_obj_loader;
 * */

void	elem_preview(wavefront_obj_loader **self, char *line) {
	char **line_split;

	line_split = ft_split(line, ' ');
	while ()
}

void	line_review(wavefront_obj_loader **self, char *line) {
	int		bytes;
	char	tmp;
	char	tmp_title[128];

	bzero(tmp_title, 128);
	if (line[0] == 'v' && line[1] == ' ') {
		bytes = sprintf(line, "%c %f %f %f", tmp, (*self)->verticies[(*self)->vert_size],
						(*self)->verticies[(*self)->vert_size + 1],
						(*self)->verticies[(*self)->vert_size + 2]);
		(*self)->vert_size += 2;
		srand(time(NULL));
		for (int i = 0; i < 3; ++i)
			(*self)->data[++(*self)->vert_size] = rand() % 256;
		(*self)->vert_size += 3;
	}
	else if (line[0] == 'o' && line[1] == ' ') {
		if ((*self)->title) {
			free((*self)->title);
			(*self)->title = NULL;
		}
		sprintf(line, "%c %s", tmp, tmp_title);
		title = ft_substr(tmp_title, 0, ft_strlen(substr));
	}
	else if (line[0] == 'f' && line[1] == ' ') {

	}
}

void 	wavefront_obj_loader_ctr(wavefront_obj_loader **self, const char *file_abspath,
				 unsigned int vert_capacity, unsigned int elem_capacity) {
	FILE			*fd;
	unsigned long	linecapp = 128;
	char			*line;

	fd = fopen(file_abspath, O_RDONLY);
	if (fd < 0) {
		char *err = "new_wavefront_obj_loader: error: ";
		char *err2 = strerror(errno);

		write(2, err, strlen(err));
		write(2, err2, strlen(err2));
		write(2, "\n", 1);
		free(*self);
		*self = NULL;
		exit -1;
	}
	(*self)->verticies = (GLfloat *)malloc(sizeof(GLfloat) * vert_capacity);
	(*self)->vert_size = 0;
	(*self)->vert_capacity = vert_capacity;
	(*self)->indicies = (GLint *)malloc(sizeof(GLint) * elem_capacity);
	(*self)->elem_size = 0;
	(*self)->elem_capacity = elem_capacity;
	title = NULL;
	while ((getline(&line, &linecapp, fd)) > 0) {

	}
}