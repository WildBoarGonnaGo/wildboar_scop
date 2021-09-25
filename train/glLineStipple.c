#include <GL/glut.h>

GLint width = 400;
GLint height = 300;

void    init() {
    glClearColor(1.0, 1.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho2D(0, 210, 0, 210);
}

void    frameDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glEnable(GL_LINE_STIPPLE);

    glLineStipple(1, 0xc0c0);
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(20.0, );
    glVertex2f(48.0, 75.0);
    glEnd();

    glLineStipple(1, 0x00ff);
    glBegin(GL_LINE_STRIP);
    glVertex2f(50.0, 75.0);
    glVertex2f(.0, 75.0);
    glEnd();
}
