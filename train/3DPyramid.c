
/*Программа для рисования пирамиды*/

#include <GL/glut.h>

void    init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 150, 0, 150, -1, 150);
}

void    display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //Включение массивов
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    GLfloat vertices[] = {
        25, 25,
        25, 125,
        125, 125,
        125, 25
    };

    GLubyte colors[] = {
        0x00, 0xcc, 0xff,
        0x00, 0xff, 0x00,
        0x99, 0x00, 0xcc,
        0x00, 0xff, 0x00
    };

    glVertexPointer(2, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

    glBegin(GL_QUADS);
    glArrayElement(0);
    glArrayElement(1);
    glArrayElement(2);
    glArrayElement(3);
    glEnd();
}
