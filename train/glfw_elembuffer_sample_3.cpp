#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void	framebuffer_func(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

void	press_input(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void) {
	GLFWwindow *window = nullptr;
	float vertex[] =  {
		-0.75f, 0.5f, 0.0f,
		-0.75f, -0.5f, 0.0f,
		0.75f, -0.5f, 0.0f,
		0.75f, 0.5f, 0.0f
	};
	GLuint index[] = {
		2, 3, 0,
		0, 1, 2
	};
	const char *sourceVertexShader =
		"# version 330 core\n"
		"layout (location = 0) in vec3 coord;\n"
		"void main() {\n;"
		"gl_Position = vec4(coord.x, coord.y, coord.z, 1.0f);\n"
		"}\0";
	const char *sourceFragmentShader =
		"# version 330 core\n"
		"out vec4 fragCore;\n"
		"void main() {\n"
		"fragCore = vec4(0.3098f, 0.52549f, 0x96863f, 1.0f);\n"
		"}\0";
	GLuint vao, vbo, ebo, vertexShader, fragmentShader, progShader;
	GLint width = 800, height = 600, success;
	char infoLog[512];
	/*initiate glfw instance with check state*/
	if (!glfwInit()) {
		std::cerr << "glfw_elembuffer_sample_3: error: glfw init error" <<
			std::endl;
		return -1;
	}
	/*Appending state options to glfw instance*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	/*window creation*/
	window = glfwCreateWindow(width, height, "Element Buffer Object (EBO)", nullptr, nullptr);
	if (!window) {
		std::cerr << "glfw_elembuffer_sample_3: error: glfw window creation error"
			<< std::endl;
		glfwTerminate();
		return -1;
	}
	/*make context if window current for main thread (rendering request)*/
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_func);
	/*GLAD loader initialization for OpenGL function*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "glfw_elembuffer_sample_3: error: glad init error"
				  << std::endl;
		glfwTerminate();
		return -1;
	}
	GLfloat glBackgrColor[] = {
		static_cast<GLfloat>(0x90)/0xff,
		static_cast<GLfloat>(0x06)/0xff,
		static_cast<GLfloat>(0x03)/0xff,
		1.0f
	};
	/*manage vertex shader*/
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &sourceVertexShader, NULL);
	glCompileShader(vertexShader);
	/*check shader compile state*/
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "glfw_elembuffer_sample_3: error: "
			<< infoLog << std::endl;
		glfwTerminate();
		return -1;
	}

	/*manage fragment shader*/
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &sourceFragmentShader, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "glfw_elembuffer_sample_3: error: "
				  << infoLog << std::endl;
		glfwTerminate();
		return -1;
	}

	/*manage final shader program*/
	progShader = glCreateProgram();
	glAttachShader(progShader, vertexShader);
	glAttachShader(progShader, fragmentShader);
	glLinkProgram(progShader);
	glGetProgramiv(progShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(progShader, 512, NULL, infoLog);
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "glfw_elembuffer_sample_3: error: "
				  << infoLog << std::endl;
		glfwTerminate();
		return -1;
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteProgram(progShader);
	}

	/*generate corresponding verticies*/
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	/*binding correpoding objects*/
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*wireframe mode*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	/*Render loop*/
	while (!glfwWindowShouldClose(window)) {
		press_input(window);

		glClearColor(glBackgrColor[0], glBackgrColor[1],
					 glBackgrColor[2], glBackgrColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(progShader);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(progShader);
	glfwTerminate();
	return 0;
}