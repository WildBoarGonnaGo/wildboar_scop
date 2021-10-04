//
// Created by lchantel on 02.10.2021.
//

#include <GL/glut.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define SINDELTA 0.00872653549837393496
#define COSDELTA 0.99996192306417128874
#define VERTCOUNT 4320

void    init() {
	glClearColor((GLclampf)(248.0 / 255.0), (GLclampf)(218.0 / 255.0), (GLclampf)(190. / 255.0), 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200, 0, 200, -1, 1);
}

void    errOutput(char *str) {
	write(2, str, strlen(str));
	exit (-1);
}

GLfloat *glCircle2f(GLfloat xCenter, GLfloat yCenter, GLfloat radius) {
	GLfloat xRadius = radius;
	GLfloat yRadius = 0;
	GLfloat oldXRadius = 0;
	GLfloat *circle = (GLfloat *)malloc(sizeof(GLfloat) * 4320);
	if (!circle)
		return (NULL);
	for (int i = 0; i < 4320; ) {
		circle[i++] = xCenter + xRadius;
		circle[i++] = yCenter + yRadius;

		oldXRadius = xRadius;
		xRadius = COSDELTA * xRadius - SINDELTA * yRadius;
		yRadius = SINDELTA * oldXRadius + COSDELTA * yRadius;
		circle[i++] = xCenter + xRadius;
		circle[i++] = yCenter + yRadius;
		circle[i++] = xCenter;
		circle[i++] = yCenter;
	}

	return (circle);
}

void    drawCircle(GLvoid *indices, GLfloat *circle, GLfloat xCenter, GLfloat yCenter, GLfloat Radius) {
	circle = glCircle2f(xCenter, yCenter, Radius);
	if (!circle)
		errOutput("Error: memory cannot be allocated\n");
	glInterleavedArrays(GL_V2F, 0, circle);
	glDrawElements(GL_TRIANGLES, VERTCOUNT, GL_UNSIGNED_SHORT, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void    display() {
	GLfloat *circle = NULL;
	int     *elemCount = NULL;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0x70, 0x42, 0x42);
	elemCount = (int *)malloc(sizeof(int) * VERTCOUNT);
	if (!elemCount)
		errOutput("Error: memory cannot be allocated\n");
	for (int i = 0; i < VERTCOUNT; ++i)
		elemCount[i] = i;
	drawCircle(elemCount, circle, 100, 100, 80);

	free(circle);
	glColor3ub(0xe4, 0xc1, 0x84);
	drawCircle(elemCount, circle, 100, 100, 75);


	free(circle);
	glColor3ub(0x70, 0x42, 0x42);
	drawCircle(elemCount, circle, 100, 100, 19);

	free(circle);
	glColor3ub(0xe4, 0xc1, 0x84);
	drawCircle(elemCount, circle, 100, 100, 16);

	glBegin(GL_QUADS);
	glVertex2f(80, 100);
	glVertex2f(80, 120);
	glVertex2f(120, 120);
	glVertex2f(120, 100);
	glEnd();

	free(circle);
	glColor3ub(0x70, 0x42, 0x42);
	drawCircle(elemCount, circle, 86, 113, 5);

	free(circle);
	drawCircle(elemCount, circle, 114, 113, 5);

	circle = NULL;
	free(elemCount);
	elemCount = NULL;
	glFlush();
}

void    reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200, 0, 200, -1, 1);
}

int     main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(1500, 500);
	glutCreateWindow("OpenGL final vertices trial");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return (0);
}

