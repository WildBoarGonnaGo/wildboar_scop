#include <GL/glut.h>

GLint width = 400;
GLint height = 300;

void    init() {
    glClearColor(1.0, 1.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0.0, 200.0, 0.0, 180, -1.0, 1.0);
}

void    frameDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glEnable(GL_LINE_STIPPLE);

    glLineStipple(1, 0x8080);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glVertex2f(40, 150);
    glVertex2f(80, 150);
    glEnd();

    glLineStipple(1, 0x00ff);
    glBegin(GL_LINES);
    glVertex2f(80.0, 150.0);
    glVertex2f(120.0, 150.0);
    glEnd();

	glLineStipple(1, 0x8e71);
	glBegin(GL_LINE_STRIP);
	glVertex2f(120.0, 150.0);
	glVertex2f(160.0, 150.0);
	glEnd();

	glLineWidth(5.0);
	glLineStipple(1, 0x8080);
	glBegin(GL_LINES);
	glVertex2f(40, 120);
	glVertex2f(80, 120);
	glEnd();

	glLineStipple(1, 0x00ff);
	glBegin(GL_LINES);
	glVertex2f(80.0, 120.0);
	glVertex2f(120.0, 120.0);
	glEnd();

	glLineStipple(1, 0x8e71);
	glBegin(GL_LINES);
	glVertex2f(120.0, 120.0);
	glVertex2f(160.0, 120.0);
	glEnd();

	glLineWidth(1.0);
	glLineStipple(1, 0x8e71);
	glBegin(GL_LINES);
	glVertex2f(40, 90);
	glVertex2f(160, 90);
	glEnd();

	glLineStipple(1, 0x8e71);
	glBegin(GL_LINE_STRIP);
	glVertex2f(40.0, 60.0);
	glVertex2f(80.0, 60.0);
	glVertex2f(120.0, 60.0);
	glVertex2f(160.0, 60.0);
	glEnd();

	glLineStipple(5, 0x8e71);
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2f(40, 30);
	glVertex2f(160, 30);
	glEnd();

	glFlush();
}

void    reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 200.0, 0.0, 180, -1.0, 1.0);
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(600, 600);
	glutCreateWindow("Line Stipple Train");
	init();
	glutDisplayFunc(frameDisplay);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return (0);
}
