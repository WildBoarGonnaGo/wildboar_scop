#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bmp_process.h>
#include <matrix.h>

void pressEsc(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void	err_println(const char *str) {
	write(2, str, strlen(str));
	write(2, "\n", 1);
}

void	err_print(const char *str) {
	write(2, str, strlen(str));
}

void	framebufferCallback(GLFWwindow *window, GLint width, GLint height) {
	glViewport(0, 0, width, height);
}

void	init_shader(GLint *id, GLint type, const char *shader_source) {
	GLint	success;
	char	infoLog[512];

	*id = glCreateShader(type);
	glShaderSource(*id, 1, &shader_source, NULL);
	glCompileShader(*id);
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if (!success) {
		err_print("glfw_rotating_cube: init_shader: ");
		glGetShaderInfoLog(*id, 512, NULL, infoLog);
		err_println(infoLog);
		*id = -1;
	}
}

int 	main(int argc, char *argv[]) {
	GLint 		width = 800, height = 600, sucess, vertexShader, fragShader, prog;
	GLuint		vao, vbo, text1, text2;
	char		infoLog[512];
	GLFWwindow	*window;

	//here the cube coordinates with texture
	GLfloat		cube_coords[] = {
		//first plane
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		//second plane
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		//third plane
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		//fourth plane
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		//fifth plane
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		//sixth plane
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};
	GLchar *vertexShaderSource = "# version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "layout (location = 1) in vec2 aTexCoord;\n"
								 "out vec2 texCoord;\n"
								 "uniform mat4 model;\n"
								 "uniform mat4 view;\n"
								 "uniform mat4 projection;\n"
								 "void main() {\n"
								 "gl_Position = vec4(aPos, 1.0f) * model * view * projection;\n"
								 "texCoord = aTexCoord;\n"
								 "}\0";
	GLchar *fragShaderSource = "# version 330 core\n"
							   "in vec2 texCoord;\n"
							   "out vec4 FragColor;\n"
							   "uniform sampler2D texture1;\n"
							   "uniform sampler2D texture2;\n"
							   "void main() {\n"
							   "FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);\n"
							   "}\0";

	if (!glfwInit()) {
		char *tmp = "glfw_rotattng_cube: error: glfw init failure";
		err_println(tmp);
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	window = glfwCreateWindow(width, height, "glfw_rotating_cube", NULL, NULL);
	if (!window) {
		char *tmp = "glfw_rotating_cube: error: window creation failure";
		err_println(tmp);
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		err_println("glfw_rotating_cube: error: glad initialization error");
		glfwTerminate();
		exit (-1);
	}

	init_shader(&vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
	if (vertexShader == -1) {
		glfwTerminate();
		return -1;
	}
	init_shader(&fragShader, GL_FRAGMENT_SHADER, fragShaderSource);
	if (fragShader == -1) {
		glfwTerminate();
		return -1;
	}

	prog = glCreateProgram();
	glAttachShader(prog, vertexShader);
	glAttachShader(prog, fragShader);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_COMPILE_STATUS, &sucess);
	if (!sucess) {
		char *tmp = "glfw_texture_sample: ";
		glGetProgramInfoLog(prog, 512, NULL, infoLog);
		err_print(tmp);
		err_println(infoLog);
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
		exit -1;
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenTextures(1, &text1);
	glGenTextures(1, &text2);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, text1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_coords), cube_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(prog);
	glUniform1i(glGetUniformLocation(prog, "texture1"), 0);
	glUniform1i(glGetUniformLocation(prog, "texture2"), 1);

	//model matrix complex revolution factors
	float	rev_fact[] = {0.5f, 1.0f, 1.0f};

	//view matrix
	matrix	*view = new_matrix_glspec();
	float	trans[] = {0.0f, 0.0f, -3.0f};
	matrix_trans(&view, trans);

	//projection matrix
	matrix	*projection = matrix_perspective_ret(M_PI / 4, 800.0f / 600.0f, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window)) {

		pressEsc(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(prog);
		//projection matrix location
		int projLoc = glGetUniformLocation(prog, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection->data);
		//view matrix location
		int viewLoc = glGetUniformLocation(prog, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view->data);
		/*model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
			glm::vec3(0.5f, 1.0f, 0.0f));*/
		//model matrix location
		//matrix	*model = matrix_multi_rev_ret(glfwGetTime() * M_PI * 50.0f / 180.0f, rev_fact);
		matrix	*model = new_matrix_glspec();
		matrix_rev_y(&model, glfwGetTime() * M_PI * 50.0f / 180.0f);
		matrix_rev_x(&model, glfwGetTime() * M_PI * 50.0f / 180.0f);
		matrix_rev_z(&model, glfwGetTime() * M_PI * 25.0f / 180.0f);
		int		modelLoc = glGetUniformLocation(prog, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model->data);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, text1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, text2);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		delete_matrix(&model);
	}
	delete_bmpProc(&texture_1);
	delete_bmpProc(&texture_2);
	delete_matrix(&view);
	delete_matrix(&projection);
	glfwTerminate();
	return 0;
}