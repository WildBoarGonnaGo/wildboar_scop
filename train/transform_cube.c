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
	gluLookAt(0.0, 0.0, 5.0)
}