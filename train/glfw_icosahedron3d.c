//
// Created by WildBoarGonnaGo on 24.10.2021.
//

/*This code is also for glfw train and is used for programming in mac for the most part
  To use GL/glew you should also include /opt/homebrew/include/ directory in include directories section*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#define GOLDRATIO 1.6180339887498948482
#define EDGE 1


int glfw_strlen(char *str) {
    int len = 0;

	if (!str)
		return (len);
    while (str[len])
        ++len;
    return (len);
}

void	init() {
	glColor3ub(0x6f, 0xb7, 0xdf);
	GLfloat mat_specular[] = {(GLfloat)(0x6f / 255), (GLfloat)(0xb7 / 255), (GLfloat)(0xdf / 255), 0.5};
	GLfloat mat_shininess[] = {100.0};
	GLfloat light_position[] = {-0.25, -0.2, 0.4, 0};
	GLfloat white_light[] = {(GLfloat)(0x6f / 255.0), (GLfloat)(0xb7 / 255.0), (GLfloat)(0xdf / 255.0), 0.5};

	glClearColor((GLclampf)(0xe3 / 255.0),
				 (GLclampf)(0xe4 / 255.0),
				 (GLclampf)(0xe6 / 255.0),
				 0);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef(45, 0, 0, 1.0);
	glRotatef(60, 1.0, 0, 0);
	glOrtho(-2, 2, -2, 2, -2, 2);
}

GLfloat **unitNormalArray3f(GLubyte (*indicies)[3], GLfloat (*vertices)[3], GLsizei numOfFaces) {
	GLfloat **unitNormals = (GLfloat **)malloc(sizeof(GLfloat *) * numOfFaces);

	if (!unitNormals)
		return (NULL);
	for (int i = 0; i < numOfFaces; ++i ) {
		GLfloat vec_1[3];
		GLfloat vec_2[3];
		GLfloat res;

		unitNormals[i] = (GLfloat *)malloc(sizeof(GLfloat) * 3);
		if (!unitNormals[i])
			return (NULL);
		vec_1[0] = vertices[indicies[i][1]][0] - vertices[indicies[i][0]][0];
		vec_1[1] = vertices[indicies[i][1]][1] - vertices[indicies[i][0]][1];
		vec_1[2] = vertices[indicies[i][1]][2] - vertices[indicies[i][0]][2];

		vec_2[0] = vertices[indicies[i][2]][0] - vertices[indicies[i][0]][0];
		vec_2[1] = vertices[indicies[i][2]][1] - vertices[indicies[i][0]][1];
		vec_2[2] = vertices[indicies[i][2]][2] - vertices[indicies[i][0]][2];

		unitNormals[i][0] = vec_1[1] * vec_2[2] - vec_1[2] * vec_2[1];
		unitNormals[i][1] = vec_1[2] * vec_2[0] - vec_1[0] * vec_2[2];
		unitNormals[i][2] = vec_1[0] * vec_2[1] - vec_1[1] * vec_2[0];
		res = sqrt(pow(unitNormals[i][0], 2) + pow(unitNormals[i][1], 2)
				   + pow(unitNormals[i][2], 2));

		unitNormals[i][0] /= res;
		unitNormals[i][1] /= res;
		unitNormals[i][2] /= res;
	}
	return (unitNormals);
};

void    errSysFatal() {
	char    *syserr = strerror(errno);

	write(2, syserr, glfw_strlen(syserr));
	write(2, "\n", 1);
	exit (-1);
}

void    display(GLFWwindow *window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat points[12][3] = {
			{ 0, -EDGE, GOLDRATIO }, { EDGE, -GOLDRATIO, 0 }, { GOLDRATIO, 0, EDGE },
			{ 0, EDGE, GOLDRATIO}, { -GOLDRATIO, 0, EDGE }, { -EDGE, -GOLDRATIO, 0 },
			{ 0, -EDGE, -GOLDRATIO }, { GOLDRATIO, 0, -EDGE }, { EDGE, GOLDRATIO, 0 },
			{ -EDGE, GOLDRATIO, 0 }, { -GOLDRATIO, 0, -EDGE }, { 0, EDGE, -GOLDRATIO }
	};

	GLubyte faces[20][3] = {
			{ 0, 1, 2 }, { 0, 2, 3 }, { 0, 3, 4 }, { 0, 4, 5 },
			{ 0, 5, 1 }, { 1, 6, 7 }, { 1, 7, 2 }, { 2, 7, 8 },
			{ 2, 8, 3 }, { 3, 8, 9 }, { 3, 9, 4 }, { 4, 9, 10 },
			{ 4, 10, 5 }, { 5, 10, 6 }, { 5, 6, 1 }, { 11, 8, 7 },
			{ 11, 9, 8 }, { 11, 10, 9 }, { 11, 6, 10 }, { 11, 7, 6 }
	};

	GLfloat **unitNormal = unitNormalArray3f(faces, points, 20);
	if (!unitNormal)
		errSysFatal();
	for (int i = 0; i < 20; ++i) {
		glColor3ub(0x6f, 0xb7, 0xdf);
		glBegin(GL_TRIANGLES);
		glNormal3fv(*(unitNormal + i));
		glVertex3fv(points[faces[i][0]]);
		glNormal3fv(*(unitNormal + i));
		glVertex3fv(points[faces[i][1]]);
		glNormal3fv(*(unitNormal + i));
		glVertex3fv(points[faces[i][2]]);
		glEnd();

		glColor3ub(0x65, 0x6e, 0x73);
		glBegin(GL_LINES);
		for (int j = 0; j < 3; ++j) {
			glVertex3fv(points[faces[i][j]]);
			glVertex3fv(points[faces[i][(j + 1) % 3]]);
		}
		glEnd();
		free(unitNormal[i]);
		unitNormal[i] = NULL;
	}

	free(unitNormal);
	unitNormal = NULL;
	//glFlush();
}

void  reshape(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(45, 0, 0, 1.0);
	glRotatef(60, 1.0, 0, 0);
	glOrtho(-2, 2, -2, 2, -2, 2);
}

int main(int argc, char *argv[]) {
    //start GL context and window using GLFW
	int	running = 1;

    if (!glfwInit()) {
        char    errGflwInit[] = "Error: GLFW environment can't be initialized\n";
        write(2, errGflwInit, glfw_strlen(errGflwInit));
        return (1);
    }

    /*Setting window properties
     GLFW_CONTEXT_VERSION_MAJOR AND GLFW_CONTEXT_VERSION MINOR - specify the client API
     version that created context might compatible with.
     macOS important note - the OS only supports forward compatible core profile for OpenGL
     versions 3.2 or later. Before creating OpenGL context of version 3.2 or later
     you must set GLFW_OPENGL_FORWARD_COMPAT and GLFW_OPENGL_PROFILE hints accordingly.
     OpenGL 3.0 and OpenGL 3.1 context are not supported on macOS at all*/
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	//glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Actually create window
    GLFWwindow *somewindow = glfwCreateWindow(640, 480, "GLFW icosahedron 3D", NULL, NULL);
    if (!somewindow) {
        char    errGlfwCreateWindow[] = "Error: GLFW window can't be created\n";
        write(2, errGlfwCreateWindow, glfw_strlen(errGlfwCreateWindow));
        glfwTerminate();
        return (1);
    }
    /*This function makes the OpenGL or OpenGL ES context of the window (in our case - somewindow)
     current on a calling thread. The context must only be made current on a single thread at a time
     and each thread can have only have a single current context in a time*/
    glfwMakeContextCurrent(somewindow);
	//gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

    //start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    //get OpenGL vesion and other miscalennious info
    const GLubyte		*OpenGLversionStr = glGetString(GL_VERSION);
    const GLubyte		*OpenGLrenderStr = glGetString(GL_RENDERER);

	write(1, "OpenGL version: ", glfw_strlen("OpenGL version: "));
	write(1, (char *)OpenGLversionStr, glfw_strlen((char *)OpenGLversionStr));
	write(1, "\n", 1);

	write(1, "OpenGL renderer: ", glfw_strlen("OpenGL renderer: "));
	write(1, (char *)OpenGLrenderStr, glfw_strlen((char *)OpenGLrenderStr));
	write(1, "\n", 1);

	init();
	glfwSetWindowSizeCallback(somewindow, reshape);
	while (!glfwWindowShouldClose(somewindow)) {
		display(somewindow);

		glfwSwapBuffers(somewindow);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}

