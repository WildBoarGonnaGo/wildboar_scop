#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void esq_query(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebufferCallback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	GLint width = 800, height = 600;
	GLuint vao[2], vbo[2], vertexShader, fragShader;
	GLFWwindow *window = nullptr;
	GLfloat tr1[] = {
			-0.5f, -0.25f, 0.0f,
			-0.25f, 0.25f, 0.0f,
			0.0f, -0.25f, 0.0f
	};
	GLfloat tr2[] = {
			0.5f, -0.25f, 0.0f,
			0.25f, 0.25f, 0.0f,
			0.0f, -0.25f, 0.0f
	};
	if (!glfwInit()) {
		std::cerr << "glfw_exc_2vao_2vbo: error: glfw init failed" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(width, height, "exc_2", NULL, NULL);
	if (!window) {
		std::cerr << "test: error: failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "test: error: failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallback);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		esq_query(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}