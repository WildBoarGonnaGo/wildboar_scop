
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void	framebuffer_size_cback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void	drawTriangle(GLuint shaderProgam, GLuint vao) {
	glUseProgram(shaderProgam);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void) {

	GLFWwindow *window = nullptr;
	GLfloat verticies[] = {
			0.0f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f
			-0.5f, -0.5f, 0.0f
	};
	unsigned int vao, vbo, fragShader, shaderProgram;
	GLint success;
	char infoLog[512];

	if (!glewInit())
		return -1;

	if (!glfwInit())
	{
		std::cerr << "glfw_sample_2: error: glfw initialization failed"
				  << std::endl;
		return -1;
	}
	/*Parameters for glfw window in macos*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(1024, 768, "Triangle", NULL, NULL);
	if (!window)
	{
		std::cerr << "glfw_sample_2: error: glfw window creation failed"
				  << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glClearColor(0.2f, 0.3f, 0.3f,1.0f);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_cback);

	/*vertex shader*/
	char *vertexInput = "#version 330 core\n"
						"layout (location = 0) in vec3 tri;\n"
						"void main() {\n"
						"\tgl_Position = vec4(tri.x, tri.y, tri.z, 1.0);\n"
						"}\0";
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexInput, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "glfw_sample_2: error: shader compilation failed" <<
				  infoLog << std::endl;
		glfwTerminate();
		glDeleteShader(vertexShader);
		return -1;
	}

	/*fragment shader*/
	char *fragOutput = "# version 330 core\n"
					   "out vec4 fragColor;\n"
					   "void main() {\n"
					   "fragColor = vec4((0x4f / 0xff)f, ( 0x86/ 0xff )f,"
					   " (0xf7 / 0xff)f);\n"
					   "}\0";
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragOutput, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cerr << "glfw_sample_2: error: shader compilation failed" <<
				  infoLog << std::endl;
		glfwTerminate();
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
		return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void *)0x0);
	glEnableVertexAttribArray(0);

	/*Compile shader program*/
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cerr << "glfw_sample_2: error: shader compilation failed" <<
				  infoLog << std::endl;
		glfwTerminate();
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
		return -1;
	}

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		drawTriangle(shaderProgram, vao);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}