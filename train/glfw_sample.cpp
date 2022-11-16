/* Ask for an OpenGL Core Context */
#define GLFW_INCLUDE_GLCOREARB
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void	framebuffer_size_cback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void	processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char** argv)
{
	GLFWwindow* window;

	/* Initialize the library */
	if ( !glfwInit() )
	{
		std::cerr << "glfw initialization failure!" << std::endl;
		return -1;
	}

	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow( 1280, 720, "Hello World", NULL, NULL );
	if (!window)
	{
		glfwTerminate();
		std::cerr << "window can't be created" << std::endl;
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glClearColor(0.2f, 0.3f, 0.3f,1.0f);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_cback);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* input process */
		processInput(window);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT); // Clear the buffers

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}