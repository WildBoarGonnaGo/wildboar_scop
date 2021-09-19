//
// Created by lchantel on 19.09.2021.
// Небольшая программа по вращению куба с использованием иструментов GLUT

#include <GL/glut.h>

GLfloat spin = 0.0;

void    init () {
	/* void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
	 - задает цвет содержимого при очистке окна. всего 4 аргумента.
	 отвечающие соответственно за красный, зеленый,
	 голубой цвета и альфа канал*/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/*
	 void glShadeModel(GLenum mode) - отвечает за режим сглаживания. Всего
	 два возможных значения GLenum mode - GL_SMOOTH, который стоит по
	 умолчанию и дает плавное сглаживание цветов в изображении, однако
	 дорого стоит по ресурсам, и GL_FLAT который отменяет сглаживание
	 изображение, но экономит на ресурсах
	 * */
	glShadeModel(GL_FLAT);
}

void    display(void) {
	/*void glClear(GLbitfield mask) - очищает буферы до предустановленных значений.
	 * можно очищать от одного, до 4-ех возможных буферов через побитовую операцию "ИЛИ"
	 (например glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)). Всего 4 вида буфера:
	    GL_COLOR_BUFFER_BIT - обозначает буферы которые доступны для рисования на данный момент
	    GL_DEPTH_BUFFER_BIT - обозначает буфер глубины
	    GL_ACCUM_BUFFER_BIT - обозначает накопительный буфер
	    GL_STENCIL_BUFFER_BIT - обозначает буфер трафаретов*/
	glClear(GL_COLOR_BUFFER_BIT);
	/*Добавляет матрицу в стэк матриц*/
	glPushMatrix();
	/*
	 glRotatef(GLfloat spin, GLfloat x, GLfloat y, GLfloat z) -
	 вращает на угол spin координатную систему вокруг следующих осей x (x * spin),
	 y (y * spin), и z (z * spin) в зависимости от модификаторов x, y и z
	 соответственно
	 * */
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	/*void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) -
	 рисует прямоугольник с вершинами (x1, y1, z1 = 0) и (x2, y2, z2 = 0). Аналогична следующей конструкции:
	    glBegin(GL_POLYGON);
	    glVertex3f(-0.25, -0.25, 0);
	    glVertex3f(0.25, -0.25, 0);
	    glVertex3f(0.25, 0.25, 0);
	    glVertex3f(-0.25, 0.25, 0);
	    glEnd();*/
	glRectf(-25.0, -25.0, 25.0, 25.0);
	/*Убирает матрицу из стэка матриц*/
	glPopMatrix();
	/*void glutSwapBuffers(void) - переключает буферы отрисовки и окна*/
	glutSwapBuffers();
}

void    spinDisplay(void) {
	spin = spin + 1.0;
	spin -= (spin > 360) ? 360 : 0;
	/*void glutPostRedisplay - помечает, что текущее окно требует перерисовки*/
	glutPostRedisplay();
}

void    reshape(int w, int h) {
	/*
	 void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
	 x, y - задает положение левого-нижнего угла окна просмотра в пикселях. Изначальное значение (0, 0)
	 width, height - задает ширину и высоту окна просмотра. Если необходимо, чтобы OpenGL изображение занимало
	 все окно, что задается ширина и высота (widht и height) создаваемого окна
	 * */
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	/*
	 void glMatrixMode(GLenum mode) - определяет какая матрица является текущей
	 mode - переменная которая обозначает стэк матриц, который будет выбран для последуюших операций
	 * */
	glMatrixMode(GL_PROJECTION);
}

