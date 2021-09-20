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
    spin -= (spin > 360.0) ? 360.0 : 0;
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
     mode - переменная которая обозначает стэк матриц, который будет выбран для последуюших операций.
     Всего доступно 3 значения: GL_MODELVIEW, GL_PROJECTION, GL_TEXTURE, GL_COLOR. glMatrixMode
     устанавливает новый режим матриц. Переменная mode может принять одно из 4 значений:
         GL_MODEVLIEW - применяет последующие матричные операции к стэку матриц просмотра модели
         GL_PROJECTION - применяет последующие матричные операции к стэку матриц проекции
         GL_TEXTURE - применяет последующие матричные операции к стэку матриц текстур
         GL_COLOR - применяет последующие матричные операции к стэку матриц цвета.
     Чтобы установить, какой стэк матриц является объектом применения матричных операций, сделайте
     вызов функции glGet с аргументом GL_MATRIX_MODE. Изначальное значение GL_MATRIX_MODE - GL_MODELVIEW
	 * */
	glMatrixMode(GL_PROJECTION);
    //Заменяет текущую матрицу единичной матрицей (identity matrix - единичная матрица)
    glLoadIdentity();
    /*
    void glOrtho(GLdouble left, GLdouble right, GLdobule bottom,
                 GLdouble top, GLdouble nearVal, GLdouble farVal);
    left, right - определяет координаты левой и правой вертикальных отсекающих плоскостей
    top, bottom - определяет координаты верхней и нижней горизонтальных отсекаюищх плоскостей
    nearVal, farVal - определяет расстояние близжайших и наиболее удаленнных по глубине отсекаемые
    плоскости. Если значение отрицательное, то плоскость находится за спиной наблюдателя.

    ОПИСАНИЕ.

    glOrtho описывает производимую трансформаицю, для того, чтобы добиться параллельного процерирования.
    Текущая матрица (см. glMatrixMode) умножается на эту матрицу и результат замещает текущаю матрицу,
    как если бы glMultMatrix была вызвана следующей матрицей, как своим аргументом:

    2 / (right - left)   0                    0                          t_x
    0                    2 / (top - bottom)   0                          t_y
    0                    0                    -2 / (farVal - nearVal)    t_z
    0                    0                    0                          1

    где,

    t_x = - (right + left) / (right - left)
    t_y = - (top + bottom) / (top- bottom)
    t_z = - (farVal + nearVal) / (farVal - nearVal)
    */
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*При нажатий левой кнопки зарегистрировать
функцию фоновой обработки (поворота)
при нажатии правой, отменить регистрацию*/

void    mouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    //Запросить режим двойной буферизации
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 400);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Double buffering and animation");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();

    return (0);
}
