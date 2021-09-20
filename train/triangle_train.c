#include <GL/glut.h>

void    init(void) {
    glClearColor(1.0, 1.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void    display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0x20, 0xEE, 0xD5);
    glBegin(GL_POLYGON);
    glVertex2f(0.125, 0.125);
    glVertex2f(0.875, 0.125);
    glVertex2f(0.5, 0.875);
    glEnd();
    glFlush();
}

int     main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(200, 200);
    glutInitWindowPosition(800, 800);
    glutCreateWindow("Glut Triangle");
    glViewport(0, 0, 200, 200);
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return (0);
}
