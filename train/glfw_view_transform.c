#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <matrix.h>
#include <bmp_process.h>


void framebufferCall(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

void pressEsc(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void err_println(const char *str) {
	write(2, str, strlen(str));
	write(2, "\n", 1);
}

void err_print(const char *str) {
	write(2, str, strlen(str));
}

void init_shader(GLuint *id, GLchar *shader, GLuint type) {
	char infoLog[512];
	GLint success;

	*id = glCreateShader(type);
	glShaderSource(*id, 1, &shader, NULL);
	glCompileShader(*id);
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_texture_sample: ";
		glGetShaderInfoLog(*id, 512, NULL, infoLog);
		err_print(tmp);
		err_println(infoLog);
		exit -1;
	}
}

int main(int argc, char *argv[]) {
	char infoLog[512];
	int success;
	GLfloat verticies[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //left bottom
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  //right bottom
			0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //top right
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f  //top left
	};
	GLint indicies[] = {
			0, 1, 2,
			0, 2, 3
	};
	GLchar *vertexShaderSource = "# version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "layout (location = 1) in vec3 inColor;\n"
								 "layout (location = 2) in vec2 aTexCoord;\n"
								 "out vec4 outColor;\n"
								 "out vec2 texCoord;\n"
								 "uniform mat4 model;\n"
								 "uniform mat4 view;\n"
								 "uniform mat4 projection;\n"
								 "void main() {\n"
								 "gl_Position = vec4(aPos, 1.0f) * model * view * projection;\n"
								 "outColor = vec4(inColor, 1.0f);\n"
								 "texCoord = aTexCoord;\n"
								 "}\0";
	GLchar *fragShaderSource = "# version 330 core\n"
							   "in vec4 outColor;\n"
							   "in vec2 texCoord;\n"
							   "out vec4 FragColor;\n"
							   "uniform sampler2D texture1;\n"
							   "uniform sampler2D texture2;\n"
							   "void main() {\n"
							   "FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);\n"
							   "}\0";
	GLuint ver, frag, prog, vao, vbo, ebo, text, text2;
	GLint width = 800, height = 600;
	GLFWwindow *window = NULL;
	if (!glfwInit()) {
		char *tmp = "glfw_texture_sample: error: glfw init failure";
		err_println(tmp);
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(width, height, "glfw_texture_sample", NULL, NULL);
	if (!window) {
		char *tmp = "glfw_texture_sample: error: window creation failure";
		err_println(tmp);
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCall);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		char *tmp = "glfw_texture_sample: error: glad init failure";
		err_println(tmp);
		return -1;
	}
	init_shader(&ver, vertexShaderSource, GL_VERTEX_SHADER);
	init_shader(&frag, fragShaderSource, GL_FRAGMENT_SHADER);
	prog = glCreateProgram();
	glAttachShader(prog, ver);
	glAttachShader(prog, frag);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_texture_sample: ";
		glGetProgramInfoLog(prog, 512, NULL, infoLog);
		err_print(tmp);
		err_println(infoLog);
		glDeleteShader(ver);
		glDeleteShader(frag);
		exit -1;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenTextures(1, &text);
	glGenTextures(1, &text2);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, text);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//set the texture wrapping and filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//load and generate the texture
	bmpProc *texture_1 = new_bmpProc(argv[1]);
	if (texture_1->texel) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_1->width, texture_1->height, 0,
					 GL_BGR, GL_UNSIGNED_BYTE, texture_1->texel);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, text2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	bmpProc *texture_2 = new_bmpProc(argv[2]);
	if (texture_2->texel) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_2->width, texture_2->height, 0,
					 GL_BGRA, GL_UNSIGNED_BYTE, texture_2->texel);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(prog);
	glUniform1i(glGetUniformLocation(prog, "texture1"), 0);
	glUniform1i(glGetUniformLocation(prog, "texture2"), 1);

	//View transformation to 3d view
	//model
	matrix	*model = new_matrix_glspec();
	matrix_rev_x(&model, -55.0f * M_PI / 180.0f);
	printf("model matrix:\n");
	for (int i = 0; i < model->rows; ++i) {
		for (int j = 0; j < model->columns; ++j) {
			printf("%.3f ", model->data[i * model->columns + j]);
		}
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
	//view matrix by translating model along 'z' axis
	//note that we're translating the scene in reverse direction
	matrix	*view = new_matrix_glspec();
	float	view_trans[] = {0.0f, 0.0f, -3.0f};
	matrix_trans(&view, view_trans);
	printf("view matrix:\n");
	for (int i = 0; i < view->rows; ++i) {
		for (int j = 0; j < view->columns; ++j) {
			printf("%.3f ", view->data[i * view->columns + j]);
		}
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
	/*
	 glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
	100.0f);
	 * */
	matrix	*proj = matrix_perspective_ret(30.0f * M_PI / 180.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	printf("projection matrix:\n");
	for (int i = 0; i < proj->rows; ++i) {
		for (int j = 0; j < proj->columns; ++j) {
			printf("%.3f ", proj->data[i * proj->columns + j]);
		}
		write(1, "\n", 1);
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		pressEsc(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(prog);
		//projection matrix location
		int projLoc = glGetUniformLocation(prog, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj->data);
		//view matrix location
		int viewLoc = glGetUniformLocation(prog, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view->data);
		//model matrix location
		int	modelLoc = glGetUniformLocation(prog, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model->data);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, text);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, text2);
		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(prog);
	delete_matrix(&model);
	delete_matrix(&view);
	delete_matrix(&proj);
	delete_bmpProc(&texture_1);
	glfwTerminate();
}