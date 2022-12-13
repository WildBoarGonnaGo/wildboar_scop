#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void frameBufferCall(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void esc_key(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void wildCompileShader(GLuint *data, GLenum type, char *source) {
	GLint success;
	char infoLog[512] = {0};

	*data = glCreateShader(type);
	glShaderSource(*data, 1, &source, NULL);
	glCompileShader(*data);
	glGetShaderiv(*data, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "exc_2: ";
		glGetShaderInfoLog(*data, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1 );
		glfwTerminate();
		exit(-1);
	}
}

void wildProgCompile(GLuint vecShader, GLuint fragShader, GLuint *prog) {
	GLint success;
	char infoLog[512];

	*prog = glCreateProgram();
	glAttachShader(*prog, vecShader);
	glAttachShader(*prog, fragShader);
	glLinkProgram(*prog);
	glGetProgramiv(*prog, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "exc_2: ";
		glGetProgramInfoLog(*prog, 512, NULL, infoLog);
		write(2, tmp, strlen(tmp));
		write(2, infoLog, strlen(infoLog));
		write(2, "\n", 1 );
		glDeleteShader(vecShader);
		glDeleteShader(fragShader);
		glfwTerminate();
		exit (-1);
	}
	glDeleteShader(vecShader);
	glDeleteShader(fragShader);
}

void verticiesInit(GLuint *vao, GLuint *vbo, GLfloat v[], GLint i, GLint size) {
	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);
	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, size, v, GL_STATIC_DRAW);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main(void) {
	GLFWwindow *window;
	int width = 800, height = 600;
	GLuint vao[2], vbo[2], vertexShader, fragShader, prog;
	GLfloat tri_1[] = {
			0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
	};
	GLfloat tri_2[] = {
			0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
	};
	char *sourceVertex_1 = "# version 330 core\n"
						   "layout (location = 0) in vec3 tri_1;\n"
						   "void main() {\n"
						   "gl_Position = vec4(tri_1.x, tri_1.y, tri_1.z, 1.0f);\n"
						   "}\0";
	char *sourceFrag_1 = "# version 330 core\n"
					   "out vec4 fragVec;\n"
					   "void main() {\n"
					   "fragVec = vec4(0.804f, 0.498f, 0.196f, 1.0f);\n"
					   "}\0";
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

	wildCompileShader(&vertexShader, GL_VERTEX_SHADER, sourceVertex_1);
	wildCompileShader(&fragShader, GL_FRAGMENT_SHADER, sourceFrag_1);
	wildProgCompile(vertexShader, fragShader, &prog);
	verticiesInit(&vao[0], &vbo[0], tri_1, 0, sizeof(tri_1));
	verticiesInit(&vao[1], &vbo[1], tri_2, 0, sizeof(tri_2));

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		esc_key(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(prog);
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}