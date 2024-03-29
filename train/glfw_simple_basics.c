//
// Created by WildBoarGonnaGo on 25.10.2021.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

void error ( int error, const char * description )
{
	fputs ( description, stderr );
}

void key ( GLFWwindow * window, int key, int scancode, int action, int mods )
{
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose ( window, GL_TRUE );
}

void display ( GLFWwindow * window )
{
	int width, height;

	glfwGetFramebufferSize ( window, &width, &height );

	float   ratio = width / (float) height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}

int main ()
{
	glfwSetErrorCallback ( error );

	if ( !glfwInit() )
		exit ( 1 );

	GLFWwindow * window = glfwCreateWindow ( 640, 480, "Simple example", NULL, NULL );

	if ( !window )
	{
		glfwTerminate ();
		exit ( 1 );
	}

	glfwMakeContextCurrent ( window );
	glfwSwapInterval       ( 1 );
	glfwSetKeyCallback     ( window, key);

	while ( !glfwWindowShouldClose ( window ) )
	{
		display ( window );
		glfwSwapBuffers ( window );
		glfwPollEvents  ();
	}

	glfwDestroyWindow ( window );
	glfwTerminate     ();

	return 0;
}