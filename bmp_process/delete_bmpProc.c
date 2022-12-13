#include "bmp_process.h"

void delete_bmpProc(bmpProc **this) {
	bmp_proc_dtor(this);
	free(*this);
	*this = NULL;
}

