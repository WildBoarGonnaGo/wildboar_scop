#include "bmp_process.h"
#include <string.h>

bmpProc *new_bmpProc(const char *filename) {
	bmpProc *self = (bmpProc *)malloc(sizeof(bmpProc));
	if (!self) {
		char *tmp = "new_bmpProc: error: ";
		char *error = strerror(ENOMEM);

		write(2, tmp, strlen(tmp));
		write(2, error, strlen(error));
		putchar('\n');
		exit (-1);
	}
	bmp_proc_ctor(&self, filename);
	return self;
}