#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <wavefront_obj_loader.h>
#include <matrix.h>
#include <bmp_process.h>

void pressEsc(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void changeTexture(GLFWwindow *window, wavefront_obj_loader **self) {
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		(*self)->texture ^= 1;
}

void moveScene(GLFWwindow *window, matrix **view) {
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		GLfloat	trans[] = { -0.02f, 0.0f, 0.0f };
		matrix_trans(view, trans);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		GLfloat	trans[] = { 0.02f, 0.0f, 0.0f };
		matrix_trans(view, trans);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		GLfloat	trans[] = { 0.0f, 0.02f, 0.0f };
		matrix_trans(view, trans);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		GLfloat	trans[] = { 0.0f, -0.02f, 0.0f };
		matrix_trans(view, trans);
	}
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
		GLfloat	trans[] = { 0.0f, 0.0f, -0.02f };
		matrix_trans(view, trans);
	}
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
		GLfloat	trans[] = { 0.0f, 0.0f, 0.02f };
		matrix_trans(view, trans);
	}
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
		ft_putstr_fd("scop: init_shader: ", 2);
		glGetShaderInfoLog(*id, 512, NULL, infoLog);
		ft_putendl_fd(infoLog, 2);
		*id = -1;
	}
}

void	init_prog(GLint *prog, GLint vertex, GLint fragment) {
	GLint	success;
	char	infoLog[512];

	*prog = glCreateProgram();
	glAttachShader(*prog, vertex);
	glAttachShader(*prog, fragment);
	glLinkProgram(*prog);
	glGetProgramiv(*prog, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "scop: ";
		glGetProgramInfoLog(*prog, 512, NULL, infoLog);
		ft_putstr_fd(tmp, 2);
		ft_putendl_fd(infoLog, 2);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		*prog = -1;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		ft_putendl_fd("scop: not enough arguments\n", 2);
		return (-1);
	}

	//check file extensions
	char	*obj_file = ft_strrchr(argv[1], '.');
	char	*bmp_file = ft_strrchr(argv[2], '.');
	if (ft_strlen(obj_file + 1) != 3 || ft_strncmp(obj_file + 1, "obj", ft_strlen(obj_file + 1))) {
		ft_putendl_fd("scop: the first arguments should be the obj file", 2);
		return (-1);
	}
	if (ft_strlen(bmp_file + 1) != 3 || ft_strncmp(bmp_file + 1, "bmp", ft_strlen(bmp_file + 1))) {
		ft_putendl_fd("scop: the second argument should be the bmp file", 2);
		return (-1);
	}

	GLint		width = 1920, height = 1080;
	GLFWwindow	*window;
	GLuint		vao, vbo, text;
	GLint		vertexShader, fragShader, prog;
	GLchar *vertexShaderSource = "# version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "layout (location = 1) in vec3 inColor;\n"
								 "layout (location = 2) in vec2 aTexCoord;\n"
								 "out vec4 outColor;\n"
								 "out vec2 texCoord;\n"
								 "uniform mat4 model;\n"
								 "uniform mat4 view;\n"
								 "uniform mat4 projection;\n"
								 "uniform float minX;\n"
								 "uniform float minY;\n"
								 "uniform float minZ;\n"
								 "uniform float maxX;\n"
								 "uniform float maxY;\n"
								 "uniform float maxZ;\n"
								 "out vec3 newPos;"
								 "void main() {\n"
								 "newPos = aPos - (vec3(minX, minY, minZ) + (vec3(maxX, maxY, maxZ) - vec3(minX, minY, minZ)) / 2);\n"
								 "gl_Position = projection * view * model * vec4(newPos, 1.0f);\n"
								 "outColor = vec4(inColor, 1.0f);\n"
								 "texCoord = aTexCoord;\n"
								 "}\0";
	GLchar *fragShaderSource = "# version 330 core\n"
							   "in vec4 outColor;\n"
							   "in vec2 texCoord;\n"
							   "out vec4 FragColor;\n"
							   "uniform sampler2D ourTexture;\n"
							   "uniform int if_texture;\n"
							   "void main() {\n"
							   "if (if_texture == 0)\n	FragColor = outColor;\n"
							   "else\n	FragColor = texture(ourTexture, texCoord);\n"
							   "}\0";
	wavefront_obj_loader *test = new_wavefront_obj_loader(argv[1], 32, 32);
	printf("verticies info:\n");
	for (int i = 0; i < test->vert_size; ++i) {
		printf("%f%c", test->verticies[i], ((i + 1) % 8) ? ' ' : '\n');
	}

	printf("\nelements info:\n");
	for (int i = 0; i < test->elem_size; ++i)
		printf("%d%c", test->indicies[i], ((i + 1) % 3) ? ' ' : '\n');

	printf("\noutput info:\n");
	for (int i = 0; i < test->output_size; ++i)
		printf("%f%c", test->output[i], ((i + 1) % 8) ? ' ' : '\n');
	printf("\nnumber of triangles: %lu\n", test->output_size / 8);
	//glfw initialization
	if (!glfwInit()) {
		char *tmp = "glfw_rotattng_cube: error: glfw init failure";
		ft_putendl_fd(tmp, 2);
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(width, height, realpath(argv[1], NULL), NULL, NULL);
	if (!window) {
		char *tmp = "scop: error: window creation failure";
		ft_putendl_fd(tmp, 2);
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		ft_putendl_fd("scop: error: glad initialization error", 2);
		glfwTerminate();
		exit (-1);
	}

	//shader compilation
	init_shader(&vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
	if (vertexShader == -1) {
		glfwTerminate();
		delete_wavefront_obj_loader(&test);
		return (-1);
	}
	init_shader(&fragShader, GL_FRAGMENT_SHADER, fragShaderSource);
	if (vertexShader == -1) {
		glfwTerminate();
		glDeleteShader(vertexShader);
		delete_wavefront_obj_loader(&test);
		return (-1);
	}
	init_prog(&prog, vertexShader, fragShader);
	if (prog == -1) {
		glfwTerminate();
		delete_wavefront_obj_loader(&test);
	}
	//objects initialization
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenTextures(1, &text);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, text);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//set the texture wrapping and filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//load and generate the texture
	bmpProc *texture_1 = new_bmpProc(argv[2]);
	if (texture_1->texel) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_1->width, texture_1->height, 0,
					 GL_BGR, GL_UNSIGNED_BYTE, texture_1->texel);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * test->output_size , test->output, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(prog);
	glUniform1i(glGetUniformLocation(prog, "ourTexture"), 0);

	//model matrix
	matrix	*model = new_matrix_glspec();

	//view matrix
	matrix	*view = new_matrix_glspec();
	float	view_trans[] = {0.0f, 0.0f, -7.0f};
	matrix_trans(&view, view_trans);

	//projection matrix
	matrix	*projection = matrix_perspective_ret(M_PI / 4, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	printf("\nminimum x: %f\n", test->xy_bound[0]);
	printf("maximum x: %f\n", test->xy_bound[1]);
	printf("minimum y: %f\n", test->xy_bound[2]);
	printf("maximum y: %f\n", test->xy_bound[3]);
	printf("minimum z: %f\n", test->xy_bound[4]);
	printf("maximum z: %f\n", test->xy_bound[5]);
	while (!glfwWindowShouldClose(window)) {
		pressEsc(window);
		changeTexture(window, &test);
		moveScene(window, &view);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(prog);

		//model boundaries
		glUniform1f(glGetUniformLocation(prog, "minX"), test->xy_bound[0]);
		glUniform1f(glGetUniformLocation(prog, "maxX"), test->xy_bound[1]);
		glUniform1f(glGetUniformLocation(prog, "minY"), test->xy_bound[2]);
		glUniform1f(glGetUniformLocation(prog, "maxY"), test->xy_bound[3]);
		glUniform1f(glGetUniformLocation(prog, "minZ"), test->xy_bound[4]);
		glUniform1f(glGetUniformLocation(prog, "maxZ"), test->xy_bound[5]);

		//texture trigger
		glUniform1i(glGetUniformLocation(prog, "if_texture"), test->texture);

		//projection matrix location
		int projLoc = glGetUniformLocation(prog, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_TRUE, projection->data);
		//view matrix location
		int viewLoc = glGetUniformLocation(prog, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view->data);
		matrix_rev_y(&model, 0.01);
		int		modelLoc = glGetUniformLocation(prog, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model->data);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, text);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, test->output_size / 8);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		usleep(10000);
	}
	glfwTerminate();
	delete_bmpProc(&texture_1);
	delete_matrix(&model);
	delete_matrix(&view);
	delete_matrix(&projection);
	delete_wavefront_obj_loader(&test);
	return 0;
}