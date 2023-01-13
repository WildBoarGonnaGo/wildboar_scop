#include "bmp_process.h"

#include <fcntl.h>
#include <string.h>

/*
 typedef struct _bmpProc {
	int width;
	int height;
	unsigned int imgSize;
 	char *texel;
} bmpProc;

 * */

void readErrPrintln(bmpProc **this) {
	char *tmp = "bmp_proc_ctor: error: ";
	write(2, tmp, strlen(tmp));
	write(2, strerror(errno), strlen(strerror(errno)));
	putchar('\n');
	delete_bmpProc(this);
	exit (-1);
}

void bmp_proc_ctor(bmpProc **this, const char *filename) {
	char info[2048];
	int fd;
	ssize_t byte;

	(*this)->texel = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		readErrPrintln(this);
	byte = read(fd, info, 54);
	if (byte <= 0) {
		char *tmp = "new_bmpProc: error: ";
		char *error = strerror(errno);

		write(2, tmp, strlen(tmp));
		write(2, error, strlen(error));
		putchar('\n');
		exit (-1);
	}
	(*this)->width = *(int *)&info[0x12];
	(*this)->height = *(int *)&info[0x16];
	(*this)->startData = *(int *)&info[0x0a];
	(*this)->imgSize = *(int *)&info[0x22];
	if (!(*this)->imgSize)
		(*this)->imgSize = (*this)->width * (*this)->height * 3;
	(*this)->texel = (char *)malloc((*this)->imgSize );
	if ((*this)->startData != 54) {
		byte = read(fd, info, (*this)->startData - 54);
		if (byte <= 0)
			readErrPrintln(this);
	}
	byte = read(fd, (*this)->texel, (*this)->imgSize);
	if (byte <= 0)
		readErrPrintln(this);
	close(fd);
}