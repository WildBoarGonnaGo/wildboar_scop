//
// Created by WildBoarGonnaGo on 25.10.2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define GL_SILENCE_DEPRECATION

void	init() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void	display(GLFWwindow *window) {

	//glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0xc7, 0xc6, 0xc1);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, -0.5f, 0);
	glVertex3f(-0.5f, 0.5f , 0);
	glVertex3f(0.5f, 0.5f, 0);
	glVertex3f(0.5f, -0.5f, 0);
	glEnd();
	glFlush();
}

void	reshape(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -0.5, 0.5);
	glMatrixMode(GL_MODELVIEW);
}

void	err_output(char *str) {
	write(2, str, strlen(str));
	write(2, "\n", 1);
	exit (1);
}

int		main(void) {
	if (!glfwInit())
		err_output("Error: glfw library can't be initialized\n");
	GLFWwindow	*somewindow = glfwCreateWindow(480, 480, "glfw funny face test", NULL, NULL);
	if (!somewindow) {
		glfwTerminate();
		exit(1);
	}
	init();
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);

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