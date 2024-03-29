//
// Created by lchantel on 26.09.2021.
//

#include <GL/glut.h>

int initWidth = 340;
int initHeight = 140;

void    init() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glShadeModel(GL_FLAT);
	glLoadIdentity();
	glOrtho(0, (GLdouble)initWidth, 0, (GLdouble)initHeight, -1.0, 1.0);
}

void    display() {
	glClear(GL_COLOR_BUFFER_BIT);

	/*polygon stipple of fly*/
	GLubyte fly[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x80, 0x01, 0xc0, 0x06, 0xc0, 0x03, 0x60,
		0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0c, 0x20,
		0x04, 0x18, 0x18, 0x20, 0x04, 0x0c, 0x30, 0x20,
		0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xc0, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xcc,
		0x19, 0x81, 0x81, 0x98, 0x0c, 0xc1, 0x83, 0x30,
		0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
		0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
		0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
		0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
		0x10, 0x63, 0xc6, 0x08, 0x10, 0x30, 0x0c, 0x08,
		0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08
	};
	/*polygon stipple for chess desk*/
	GLubyte chess[] = {
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55
	};

	glColor3ub(0xef, 0xfd, 0x5f);
	glBegin(GL_QUADS);
	glVertex2f(20.0, 20.0);
	glVertex2f(20.0, 120.0);
	glVertex2f(120, 120);
	glVertex2f(120, 20);
	//glRectf(20.0, 20.0, 120.0, 120.0);
	glEnd();

	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(fly);
	glBegin(GL_QUADS);
	glVertex2f(120.0, 20.0);
	glVertex2f(120, 120.0);
	glVertex2f(220, 120);
	glVertex2f(220, 20);
	glEnd();
	//glRectf(120.0, 20.0, 220.0, 120.0);

	glPolygonStipple(chess);
	glBegin(GL_QUADS);
	glVertex2f(220.0, 20.0);
	glVertex2f(220, 120.0);
	glVertex2f(320, 120);
	glVertex2f(320, 20);
	glEnd();
	//glRectf(220.0, 20.0, 320.0, 120.0);
	glDisable(GL_POLYGON_STIPPLE);

	glFlush();
}

void    reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (GLdouble)initWidth, 0, (GLdouble)initHeight, -1.0, 1.0);
}

int     main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(initWidth, initHeight);
	glutInitWindowPosition(1750, 500);
	glutCreateWindow("OpenGL Polygon Stipple");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return (0);
}