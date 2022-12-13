#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <string.h>

void framebufferCallBack(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

void pressEsc(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void) {
	GLint success;
	GLuint width = 800, height = 600, vertShader, fragShader, prog, vao, vbo;
	GLFWwindow *window = NULL;
	GLchar infoLog[512];
	GLfloat fullTri[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	const GLchar *sourceVertexShader = "# version 330 core\n"
									   "layout (location = 0) in vec3 aPos;\n"
									   "layout (location = 1) in vec3 aColor;\n"
									   "out vec4 ourColor;\n"
									   "void main() {\n"
									   "gl_Position = vec4(aPos, 1.0f);\n"
									   "ourColor = vec4(aColor, 1.0f);\n"
									   "}\0";
	const GLchar *sourceFragShader = "# version 330 core\n"
									 "in vec4 ourColor;\n"
									 "out vec4 fragColor;\n"
									 "void main() {\n"
									 "fragColor = ourColor;\n"
									 "}\0";
	if (!glfwInit()) {
		char *tmp = "glfw_tri_palete: error: glfw init failure\n";
		write(2, tmp, strlen(tmp));
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(width, height, "Triangle Palette", NULL, NULL);
	if (!window) {
		char *tmp = "glfw_tri_palete: error: can't create window\n";
		write(2, tmp, strlen(tmp));
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallBack);
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		char *tmp = "glfw_tri_palete: error: glad init failure\n";
		write(2, tmp, strlen(tmp));
		glfwTerminate();
		return -1;
	}

	// vertex shader init
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &sourceVertexShader, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_tri_palete: ";
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1);
		glfwTerminate();
		return -1;
	}

	// fragment shader init
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &sourceVertexShader, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_tri_palete: ";
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1);
		glfwTerminate();
		return -1;
	}
	// fragment shader init
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &sourceFragShader, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_tri_palete: ";
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1);
		glDeleteShader(vertShader);
		glfwTerminate();
		return -1;
	}

	//prog init
	prog = glCreateProgram();
	glAttachShader(prog, vertShader);
	glAttachShader(prog, fragShader);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_tri_palete: ";
		glGetProgramInfoLog(fragShader, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		glfwTerminate();
		return -1;
	}
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullTri), fullTri, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		pressEsc(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(prog);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}