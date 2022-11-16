
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void resize(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

void escInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
	GLFWwindow *window;
	GLuint vbo, vao, vertexId, fragId, progId;
	GLint success;
	char infoLog[512];
	float verticies[] = {
			0.0f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
	};

	if (!glfwInit()) {
		std::cerr << "glfw_sample_2: error: GLFW init failure" << std::endl;
		return (-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(800, 600, "Sample 2", NULL, NULL);
	if (!window) {
		std::cerr << "glfw_sample_2: error: window init failure" << std::endl;
		return (-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "glfw_sample_2: error: GLAD init failure" << std::endl;
		return (-1);
	};
	float clearColor[4] = { static_cast<GLfloat>(0x90)/0xff,
							static_cast<GLfloat>(0x06)/0xff,
							static_cast<GLfloat>(0x03)/0xff,
							1.0f };

	/*vertex shader init*/
	const char* vertexShader = "# version 330 core\n"
			"layout (location = 0) in vec3 trigl;\n"
			"void main() {\n"
			"gl_Position = vec4(trigl.x, trigl.y, trigl.z, 1.0);\n"
			"}\0";
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexShader, NULL);
	glCompileShader(vertexId);
	/*check vertex shader compile status*/
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
		std::cerr << "glfw_sample_2: shader compile error: "
			<< infoLog << std::endl;
	}

	/*fragment shader init*/
	const char* fragShader = "# version 330 core\n"
							 "out vec4 FragColor;\n"
							 "void main() {\n"
							 "FragColor = vec4(0.3098f, 0.52549f, 0x96863f, 1.0f);\n"
							 "}\0";
	fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, &fragShader, NULL);
	glCompileShader(fragId);
	/*check fragment shader compile status*/
	glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragId, 512, NULL, infoLog);
		std::cerr << "glfw_sample_2: shader compile error: "
				  << infoLog << std::endl;
	}

	/*program shader init*/
	progId = glCreateProgram();
	glAttachShader(progId, vertexId);
	glAttachShader(progId, fragId);
	glLinkProgram(progId);
	/*check program compilation status*/
	glGetProgramiv(progId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(progId, 512, NULL, infoLog);
		std::cerr << "glfw_sample_2: program compile error"
			<< std::endl;
	}
	glDeleteShader(vertexId);
	glDeleteShader(fragId);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	while (!glfwWindowShouldClose(window))
	{
		escInput(window);
		glClearColor(clearColor[0], clearColor[1],
			clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(progId);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(progId);
	glfwTerminate();
	return 0;
}