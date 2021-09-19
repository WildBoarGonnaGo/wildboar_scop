//
// Created by lchantel on 18.09.2021.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <string.h>
#define WINDOW_CREATE_FAIL "Failed to create GLFW window\n"
#define INIT_GLAD_FAILED "Failed to initialize GLAD"

void    framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/*For Mac OS X you should add next command
	 glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
	 */

	GLFWwindow  *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (!window) {
		write(2, WINDOW_CREATE_FAIL, strlen(WINDOW_CREATE_FAIL));
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		write(2, INIT_GLAD_FAILED, strlen(INIT_GLAD_FAILED));
		return (-1);
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}