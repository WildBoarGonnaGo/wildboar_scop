//
// Created by lchantel on 10.10.2021.
//

#include <GL/glut.h>

void    init() {
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
}

void    display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);

	/*Clear the matrix*/
	glLoadIdentity();

	/*View Matrix camera*/
	glLineWidth(3);
    gluLookAt(1.5, 1.5, 1.5, 0.0, 0.0, 0.0, -0.577, -0.577, 0.577);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /*Model transformation*/
    glScalef(1, 2, 1);
    glBegin(GL_LINES);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);

    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    glFlush();
}

void	reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.750, 0.750, -0.750, 0.750, 1, 20);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, 1, 20);
	glMatrixMode(GL_MODELVIEW);
}

int		main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(600, 500);
    glutCreateWindow("OpenGL view train");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return (0);
}
