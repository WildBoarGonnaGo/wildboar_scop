#include "bmp_process.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("test_bmp_process: wrong number of arguments\n");
		return -1;
	}

	bmpProc *self = new_bmpProc(argv[1]);
	printf("width = %d\n", self->width);
	printf("height = %d\n", self->height);
	printf("image size = %d\n", self->imgSize);
	printf("start of data: %d\n", self->startData);
	delete_bmpProc(&self);
	return (0);
}