//
// Created by WildBoarGonnaGo on 24.10.2021.
//

/*This code is also for glfw train and is used for programming in mac for the most part
  To use GL/glew you should also include /opt/homebrew/include/ directory in include directories section*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
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

}

int main(int argc, char *argv[]) {
    char    hello[] = "Hello world\n";

    write(1, hello, glfw_strlen(hello));

    //start GL context and window using GLFW
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
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

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

	while (!glfwWindowShouldClose(somewindow)) {
		glfwSwapBuffers(somewindow);
		glfwPollEvents();
	}
	//glfwTerminate();
	return (0);
}

