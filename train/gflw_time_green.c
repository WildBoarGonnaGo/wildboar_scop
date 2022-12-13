#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

void framebufferCallBack(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

int main() {
	GLFWwindow *window;
	GLint width = 800, height = 600, success;
	char infoLog[512];
	GLfloat time, green, colorInputPos;
	char *sourceVertexShader = "# version 330 core\n"
							   "layout (location = 0) in vec3 tri;\n"
							   "void main() {\n"
							   "gl_Position = vec4(tri, 1.0f);\n"
							   "}\0";
	char *sourceFragShader = "# version 330 core\n"
							 "out vec4 fragColor;\n"
							 "uniform vec4 colorInput;\n"
							 "void main() {\n"
							 "fragColor = colorInput;\n"
							 "}\0";
	GLfloat verticies[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
	};
	GLuint vao, vbo, vertexShader, fragShader, prog;
	if (!glfwInit()) {
		char *tmp = "glfw_time_green: error: glfw init failure\n";
		write(2, tmp, strlen(tmp));
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(width, height, "glfw_time_green", NULL, NULL);
	if (!window) {
		char *tmp = "glfw_time_green: error: window init failure\n";
		write(2, tmp, strlen(tmp));
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallBack);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		char *tmp = "glfw_time_green: error: glad init failure\n";
		write(2, tmp, strlen(tmp));
		glfwTerminate();
		return -1;
	}

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &sourceVertexShader, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_time_green: ";
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1);
		glfwTerminate();
		return -1;
	}
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &sourceFragShader, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_time_green: ";
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1);
		glfwTerminate();
		return -1;
	}
	prog = glCreateProgram();
	glAttachShader(prog, vertexShader);
	glAttachShader(prog, fragShader);
	glLinkProgram(prog);
	glGetProgramiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_time_green: ";
		glGetProgramInfoLog(vertexShader, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1);
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
		glfwTerminate();
		return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(prog);
		time = glfwGetTime();
		green = sin(time) / 2.0f + 0.5f;
		colorInputPos = glGetUniformLocation(prog, "colorInput");
		glUniform4f(colorInputPos, 0.0f, green, 0.0f, 1.0f);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	glDeleteProgram(prog);
	return 0;
}