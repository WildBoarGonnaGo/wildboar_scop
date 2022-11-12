//
// Created by WildBoarGonnaGo on 25.10.2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define GL_SILENCE_DEPRECATION
#define SINDELTA 0.00872653549837393496
#define COSDELTA 0.99996192306417128874
#define VERTCOUNT 4320

GLint	oldXWidth = 480;
GLint	oldYHeight = 480;

void	init() {
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

void	display(GLFWwindow *window) {
	GLfloat *circle = NULL;
	int     *elemCount = NULL;
	/*GLint	width, height, xratio, yratio;

	glfwGetWindowSize(window, &width, &height);
	xratio = width / oldXWidth;
	yratio = yratio / oldYHeight;
	glViewport(0, 0, width, height);
	glOrtho(0, 200 * xratio, 0, 200 * yratio, -1, 1);*/

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

void	reshape(GLFWwindow *window, int width, int height) {
	GLint xratio, yratio;

	xratio = oldXWidth / width;
	yratio = oldYHeight / height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200 * xratio, 0, 200 * yratio, -1, 1);
	//glMatrixMode(GL_MODELVIEW);
}

void	err_output(char *str) {
	write(2, str, strlen(str));
	write(2, "\n", 1);
	exit (1);
}

int		main(void) {
	if (!glfwInit())
		err_output("Error: glfw library can't be initialized\n");
	GLFWwindow	*somewindow = glfwCreateWindow(oldXWidth, oldYHeight, "glfw funny face test", NULL, NULL);
	if (!somewindow) {
		glfwTerminate();
		exit(1);
	}
	init();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

	glfwMakeContextCurrent(somewindow);
	glfwSwapInterval(1);
	glfwSetWindowSizeCallback(somewindow, reshape);
	while (!glfwWindowShouldClose(somewindow)) {
		display(somewindow);
		glfwSwapBuffers(somewindow);
		glfwPollEvents();
	}
	glfwDestroyWindow(somewindow);
	glfwTerminate();

	return (0);
}