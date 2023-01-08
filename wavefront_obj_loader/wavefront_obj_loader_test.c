#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <wavefront_obj_loader.h>
#include <matrix.h>


/*
typedef struct _wavefront_obj_loader {
	GLfloat 		*verticies;
	GLint			*indicies;
	unsigned int	vert_size;
	unsigned int	vert_capacity;
	unsigned int	elem_size;
	unsigned int	elem_capacity;
	char			*title;
}	wavefront_obj_loader;
*/

void pressEsc(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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
		ft_putstr_fd("glfw_rotating_cube: init_shader: ", 2);
		glGetShaderInfoLog(*id, 512, NULL, infoLog);
		ft_putendl_fd(infoLog, 2);
		*id = -1;
	}
}

int main(void) {

	char		*filename = "../models/resources/42.obj";
	GLint		width = 1360, height = 768, success;
	GLFWwindow	*window;
	GLuint		vao, vbo, ebo, prog;
	GLint		vertexShader, fragShader;
	char		infoLog[512];
	GLchar *vertexShaderSource = "# version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "layout (location = 1) in vec3 inColor;\n"
								 "layout (location = 2) in vec2 aTexCoord;\n"
								 "out vec4 outColor;\n"
								 "out vec2 texCoord;\n"
								 "uniform mat4 transform;\n"
								 "void main() {\n"
								 "gl_Position = transform * vec4(aPos, 1.0f);\n"
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
							   "FragColor = OutColor;\n"
							   "}\0";
	wavefront_obj_loader *test = new_wavefront_obj_loader(filename, 32, 32);
	printf("verticies info:\n");
	for (int i = 0; i < test->vert_size; ++i) {
		printf("%f%c", test->verticies[i], ((i + 1) % 8) ? ' ' : '\n');
	}
	printf("\nminimum x: %f\n", test->xy_bound[0]);
	printf("maximum x: %f\n", test->xy_bound[1]);
	printf("minimum y: %f\n", test->xy_bound[2]);
	printf("maximum y: %f\n", test->xy_bound[3]);

	printf("\nelements info\n");
	for (int i = 0; i < test->elem_size; ++i)
		printf("%d%c", test->indicies[i], ((i + 1) % 3) ? ' ' : '\n');

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
	window = glfwCreateWindow(width, height, test->title, NULL, NULL);
	if (!window) {
		char *tmp = "Cube: error: window creation failure";
		ft_putendl_fd(tmp, 2);
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallback);

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
		delete_wavefront_obj_loader(&test);
		return (-1);
	}
	prog = glCreateProgram();
	glAttachShader(prog, vertexShader);
	glAttachShader(prog, fragShader);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_COMPILE_STATUS, &success);
	if (!success) {
		char *tmp = "glfw_texture_sample: ";
		glGetProgramInfoLog(prog, 512, NULL, infoLog);
		ft_putstr_fd(tmp, 2);
		ft_putendl_fd(infoLog, 2);
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);
		exit -1;
	}


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		ft_putendl_fd("glfw_rotating_cube: error: glad initialization error", 2);
		glfwTerminate();
		exit (-1);
	}
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		pressEsc(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	delete_wavefront_obj_loader(&test);
}