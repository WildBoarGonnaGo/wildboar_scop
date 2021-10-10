#include <unistd.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#define GOLDRATIO 1.6180339887498948482
#define EDGE 1

GLsizei initWidth = 400;
GLsizei initHeight = 400;

void    init() {
	glColor3ub(0x6f, 0xb7, 0xdf);
	GLfloat mat_specular[] = {(GLfloat)(0x6f / 255), (GLfloat)(0xb7 / 255), (GLfloat)(0xdf / 255), 0.5};
	GLfloat mat_shininess[] = {100.0};
	GLfloat light_position[] = {-0.25, -0.2, 0.4, 0};
	GLfloat white_light[] = {(GLfloat)(0x6f / 255.0), (GLfloat)(0xb7 / 255.0), (GLfloat)(0xdf / 255.0), 0.5};

    glClearColor((GLclampf)(0xe3 / 255.0),
                 (GLclampf)(0xe4 / 255.0),
                 (GLclampf)(0xe6 / 255.0),
                 0);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glRotatef(45, 0, 0, 1.0);
	glRotatef(60, 1.0, 0, 0);
    glOrtho(-2, 2, -2, 2, -2, 2);
}

void    errSysFatal() {
	char    *syserr = strerror(errno);

	write(2, syserr, strlen(syserr));
	write(2, "\n", 1);
	exit (-1);
}

void    errUdefStr(char *str) {
	write(2, str, strlen(str));
	exit (-1);
}

GLfloat **unitNormalArray3f(GLubyte (*indicies)[3], GLfloat (*vertices)[3], GLsizei numOfFaces) {
	GLfloat **unitNormals = (GLfloat **)malloc(sizeof(GLfloat *) * numOfFaces);

	if (!unitNormals)
		return (NULL);
	for (int i = 0; i < numOfFaces; ++i ) {
		GLfloat vec_1[3];
		GLfloat vec_2[3];
		GLfloat res;

		unitNormals[i] = (GLfloat *)malloc(sizeof(GLfloat) * 3);
		if (!unitNormals[i])
			return (NULL);
		vec_1[0] = vertices[indicies[i][1]][0] - vertices[indicies[i][0]][0];
		vec_1[1] = vertices[indicies[i][1]][1] - vertices[indicies[i][0]][1];
		vec_1[2] = vertices[indicies[i][1]][2] - vertices[indicies[i][0]][2];

		vec_2[0] = vertices[indicies[i][2]][0] - vertices[indicies[i][0]][0];
		vec_2[1] = vertices[indicies[i][2]][1] - vertices[indicies[i][0]][1];
		vec_2[2] = vertices[indicies[i][2]][2] - vertices[indicies[i][0]][2];

		unitNormals[i][0] = vec_1[1] * vec_2[2] - vec_1[2] * vec_2[1];
		unitNormals[i][1] = vec_1[2] * vec_2[0] - vec_1[0] * vec_2[2];
		unitNormals[i][2] = vec_1[0] * vec_2[1] - vec_1[1] * vec_2[0];
		res = sqrt(pow(unitNormals[i][0], 2) + pow(unitNormals[i][1], 2)
				+ pow(unitNormals[i][2], 2));

		unitNormals[i][0] /= res;
		unitNormals[i][1] /= res;
		unitNormals[i][2] /= res;
	}
	return (unitNormals);
};

void    display() {
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat points[12][3] = {
			{ 0, -EDGE, GOLDRATIO }, { EDGE, -GOLDRATIO, 0 }, { GOLDRATIO, 0, EDGE },
			{ 0, EDGE, GOLDRATIO}, { -GOLDRATIO, 0, EDGE }, { -EDGE, -GOLDRATIO, 0 },
			{ 0, -EDGE, -GOLDRATIO }, { GOLDRATIO, 0, -EDGE }, { EDGE, GOLDRATIO, 0 },
			{ -EDGE, GOLDRATIO, 0 }, { -GOLDRATIO, 0, -EDGE }, { 0, EDGE, -GOLDRATIO }
	};

	GLubyte faces[20][3] = {
			{ 0, 1, 2 }, { 0, 2, 3 }, { 0, 3, 4 }, { 0, 4, 5 },
			{ 0, 5, 1 }, { 1, 6, 7 }, { 1, 7, 2 }, { 2, 7, 8 },
			{ 2, 8, 3 }, { 3, 8, 9 }, { 3, 9, 4 }, { 4, 9, 10 },
			{ 4, 10, 5 }, { 5, 10, 6 }, { 5, 6, 1 }, { 11, 8, 7 },
			{ 11, 9, 8 }, { 11, 10, 9 }, { 11, 6, 10 }, { 11, 7, 6 }
	};

	GLfloat **unitNormal = unitNormalArray3f(faces, points, 20);
	if (!unitNormal)
		errSysFatal();
	for (int i = 0; i < 20; ++i) {
		glColor3ub(0x6f, 0xb7, 0xdf);
		glBegin(GL_TRIANGLES);
		glNormal3fv(*(unitNormal + i));
		glVertex3fv(points[faces[i][0]]);
		glNormal3fv(*(unitNormal + i));
		glVertex3fv(points[faces[i][1]]);
		glNormal3fv(*(unitNormal + i));
		glVertex3fv(points[faces[i][2]]);
		glEnd();

		glColor3ub(0x65, 0x6e, 0x73);
		glBegin(GL_LINES);
		for (int j = 0; j < 3; ++j) {
			glVertex3fv(points[faces[i][j]]);
			glVertex3fv(points[faces[i][(j + 1) % 3]]);
		}
		glEnd();
		free(unitNormal[i]);
		unitNormal[i] = NULL;
	}

	free(unitNormal);
	unitNormal = NULL;
	glFlush();
}

void    reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(45, 0, 0, 1.0);
	glRotatef(60, 1.0, 0, 0);
	glOrtho(-2, 2, -2, 2, -2, 2);
}

int     main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(1500, 500);
	glutCreateWindow("OpenGL Icosahedron 3D");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

    return (0);

}
