#include <unistd.h>
#include <GL/glut.h>

void    init() {
    glClearColor((GLclampf)(0x28 / 255.0),
                 (GLclampf)(0x23 / 255.0),
                 (GLclampf)(0x1D / 255.0),
                 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 150, 0, 150, 0, 150);
}

int     main(int argc, char *argv[]) {
    return (0);
}
