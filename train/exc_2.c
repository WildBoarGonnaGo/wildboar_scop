#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <string.h>

void frameBufferCall(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void esc_key(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void) {
	GLFWwindow *window;
	int width = 800, height = 600;
	GLint vao[2], vbo[2];
	char *sourceVertex_1, *source_Vertex_2, *fragVertex;
	if (!glfwInit()) {
		char *tmp = "exc_2: error: glfw init failure";
		write(2, tmp, strlen(tmp));
		return (-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(width, height, "exc_2", NULL, NULL);
	if (!window) {
		char *tmp = "exc_2: error: window creation failure";
		write(2, tmp, strlen(tmp));
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferCall);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		char *tmp = "exc_2: error: glad init failure";
		write(2, tmp, strlen(tmp));
		glfwTerminate();
		return (-1);
	}
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}