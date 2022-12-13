#ifndef BMP_PROCESS_H
# define BMP_PROCESS_H
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>
# include <stdio.h>

typedef struct _bmpProc {
	int width;
	int height;
	unsigned int imgSize;
	int startData;
	char *texel;
} bmpProc;

bmpProc *new_bmpProc(const char *filename);
void bmp_proc_ctor(bmpProc **this, const char *filename);
void bmp_proc_dtor(bmpProc **this);
void delete_bmpProc(bmpProc **this);

#endif