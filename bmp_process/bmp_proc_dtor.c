#include "bmp_process.h"

void bmp_proc_dtor(bmpProc **this) {
	if ((*this)->texel) {
		free((*this)->texel);
		(*this)->texel = NULL;
	}
}