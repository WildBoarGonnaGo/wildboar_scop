//
// Created by lchantel on 18.09.2021.
// Работа с библиотекой управления окнами glut

#include <GL/glut.h>

void    init(void) {
	//Выбрать фоновый, очищающий цвет
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Установить проекцию
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

//Функция отрисовки белого квадрата при вызове окна
void    display(void) {
	//Очистить экран
	glClear(GL_COLOR_BUFFER_BIT);
	/*Нарисовать белый полигон (квадрат) с углами в (0.25, 0.25, 0.0), (0.75, 0.75, 0.0)*/
	glColor3ub(0xFF, 0xFE, 0xF2);
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 0.15, 0);
	glVertex3f(0.85, 0.15, 0);
	glVertex3f(0.85, 0.85, 0);
	glVertex3f(0.15, 0.85, 0);
	glEnd();
	/*Не ждем, начинаем выполнять буферизированные команды OpenGl*/
	glFlush();
}

int     main(int argc, char *argv[]) {
	/*сначала должна быть вызвана функция glutInit до
	 вызова каких либо других функций GLUT*/
	glutInit(&argc, argv);
	/*glutInitDisplayMode() - указаывает на режим отображения (например
	 RGBA или индексный, одинарной или двойной буферизации). Можно все эти
	 режимы совмещать через битовые маски. Можно совмещать следующие константы
	 (GLUT_RGBA || GLUT_INDEX) | (GLUT_SINGLE | GLUT_DOUBLE) | GLUT_DEPTH | GLUT_STENCIL | GLUT_ACCUN
	 GLUT_DEPTH, GLUT_STENCIL, GLUT_ACCUN - константы для включения различных буферов. Значение по
	 умолчанию - GLUT_RGBA | GLUT_SINGLE (окно с однократной буферизацией в RGBA режиме)*/
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	/*void glutInitWindowSize(int width, int height) - запрашивает окно определенного размера
	 width - ширина окна, height - высота окна
	 void glutInitWindowPosition(int x, int y) - запрашивают положение окна, аргументы
	 x и y определяют, где будет находиться угол окна относительно всего экрана*/
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(400, 400);
	/*
	 int glutCreateWindow(char *name) -  октрывает окно с предварительно установленными
	 характеристиками (режимом отображения размером и так далее). Строка name может
	 быть отображена в заголовке окна, но это зависит от оконной системы ОС.
	 * */
	glutCreateWindow("OpenGL GLUT train");
	/*Окно не отображается до того, как произведен вход в glutMainLoop(), поэтому
	 до вызова этой функции нельзя рисовать что-либо в окно. Возвращаемая целая
	 величина в glutCreateWindow представляет с собой уникальный идентификатор окна.
	 Этот идентификатор может быть использован для управления несколькими окнами в
	 одном приложении (каждое со своим контекстом OpenGL) и рисования в них*/
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return (0);
}