#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void	proc_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void	framebufferCallBack(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

int main(void) {
	GLint width = 1000, height = 1000, success;
	GLuint vao, vbo, ebo, vertexShader, fragShader, prog;
	GLFWwindow *window = nullptr;
	char infoLog[512];
	GLfloat verticies[] = {
		-0.4f, 0.0f, 0.0f,
		0.0f, 0.4f, 0.0f,
		0.4f, 0.0f, 0.0f,
		-0.8f, -0.4f, 0.0f,
		0.0f, -0.4f, 0.0f,
		0.8f, -0.4f, 0.0f
	};
	GLint indicies[] = {
			0, 1, 2,
			3, 4, 0,
			4, 5, 2
	};
	const char *sourceVertexShader =
			"# version 330 core\n"
			"layout (location = 0) in vec3 data;\n"
			"void main() {\n"
			"gl_Position = vec4(data.x, data.y, data.z, 1.0f);\n"
			"}\0";
	const char *sourceFragmentShader =
			"# version 330 core\n"
			"out vec4 fragData;\n"
			"void main() {\n"
			"fragData = vec4(1.0f, 0.8431387f, 0.0f, 1.0f);\n"
			"}\0";

	if (!glfwInit()) {
		std::cerr << "glfw_triforce: error: glfw init failure..." << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(width, height, "GLFW triforce", nullptr, nullptr);
	if (!window) {
		std::cerr << "glfw_triforce: error: window can't be created..." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallBack);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "glfw_triforce: error: glad init failure..." << std::endl;
		glfwTerminate();
		return -1;
	}
	glClearColor(static_cast<GLfloat>(0x79)/0xff,
				 static_cast<GLfloat>(0x5c)/0xff,
				 static_cast<GLfloat>(0x34)/0xff,
				 1.0f);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &sourceVertexShader, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "glfw_triforce: " << infoLog << std::endl;
		glfwTerminate();
		return -1;
	}
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &sourceFragmentShader, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "glfw_triforce: " << infoLog << std::endl;
		glDeleteShader(vertexShader);
		glfwTerminate();
		return -1;
	}
	prog = glCreateProgram();
	glAttachShader(prog, vertexShader);
	glAttachShader(prog, fragShader);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(prog, 512, NULL, infoLog);
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
		glfwTerminate();
		return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(prog);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(prog);
	glfwTerminate();
	return 0;
}