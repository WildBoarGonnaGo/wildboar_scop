#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void	proc_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClode(window, GL_TRUE);
}

void	framebufferCallBack(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	GLfloat verticies[] = {
		-0.4f, 0.0f, 0.0f,
		0.0f, 0.4f, 0.0f,
		0.4f, 0.0f, 0.0f,
		-0.8f, -0.4f, 0.0f
		0.0f, -0.4f, 0.0f,
		0.8f, -0.4f, 0.0f
	};

	if (!glfwInit()) {
		std::cerr << "glfw_triforce: error: glfw init failure" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwMakeContextCurrent(window)
	glfwSetFramebufferSizeCallback(window, framebufferCallBack);
	if (!gladLoadGLLoader(static_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cerr << "glfw_triforce: error: glad init failure" << std::endl;
		glfwTerminate();
		return -1;
	}
	glClearColor(static_cast<GLfloat>(0x79)/0xff,
				 static_cast<GLfloat>(0x5c)/0xff,
				 static_cast<Glfloat>(0x34)/0xff,
				 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glClearColor();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}