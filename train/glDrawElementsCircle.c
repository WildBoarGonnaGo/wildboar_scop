#include <GL/glut.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
# define SINDELTA 0.00872653549837393496
# define COSDELTA 0.99996192306417128874
# define GL_CIRCLE_ALLOC 4320

void    init() {
    glClearColor((GLclampf)(197.0 / 255.0), (GLclampf)(197.0 / 255.0),
                 (GLclampf)(189.0 / 255.0), 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 180, 0, 180, -1, 1);
}

int     wb_strlen(char *str) {
    int len = 0;

    while (*(str++))
        ++len;
    return (len);
}

int     *setIndxArray(int size) {
    int *arr;

    arr = (int *)malloc(sizeof(int) * size);
    if (!arr)
        return (NULL);
    for (int i = 0; i < size; ++i)
        arr[i] = i;
    return (arr);
}

GLfloat *glUserCircle2f(GLfloat xCenter, GLfloat yCenter, GLfloat radius) {
    GLfloat *circle;
    GLfloat xRadius;
    GLfloat yRadius = 0;
    GLfloat oldXRadius;

    xRadius = radius;
    circle = (GLfloat *)malloc(sizeof(GLfloat) * 4320);
    if (!circle)
        return (NULL);
    for (int i = 0; i < 4320; ) {
        circle[i++] = (GLfloat)(xCenter + xRadius);
        circle[i++] = (GLfloat)(yCenter + yRadius);

        oldXRadius = xRadius;
        xRadius = xRadius * COSDELTA - yRadius * SINDELTA;
        yRadius = oldXRadius * SINDELTA + yRadius * COSDELTA;
        circle[i++] = (GLfloat)(xCenter + xRadius);
        circle[i++] = (GLfloat)(yCenter + yRadius);
        circle[i++] = (GLfloat)(xCenter);
        circle[i++] = (GLfloat)(yCenter);
    }
    return (circle);
}

void    errorAlloc() {
    write(2, "Error: memory can't be assigned\n",
          wb_strlen("Error: memory can't be assigned\n"));
    exit (-1);
}

void    glDrawCircle(GLvoid *indicies, GLfloat *circle) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, (GLvoid *)circle);
    glDrawElements(GL_TRIANGLES, GL_CIRCLE_ALLOC, GL_UNSIGNED_SHORT, (GLvoid *)indicies);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void    display() {
    GLfloat *res;
    int     *indx;
    GLfloat xEye = 13.045;
    GLfloat yEye = 90 + 12.5;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0xae, 0x15, 0x0d);
    res = glUserCircle2f(90, 90, 65);
    if (!res)
        errorAlloc();
    indx = setIndxArray(GL_CIRCLE_ALLOC);
    if (!indx)
        errorAlloc();
    glDrawCircle(indx, res);

    free(res);
    res = glUserCircle2f(90, 90, 60);
    if (!res)
        errorAlloc();
    glColor3ub(0xc9, 0x80, 0x24);
    glDrawCircle(indx, res);

    free(res);
    glColor3ub(0x37, 0x30, 0x28);
    res = glUserCircle2f(90 - xEye, yEye, 7);
    if (!res)
        errorAlloc();
    glDrawCircle(indx, res);

    free(res);
    res = glUserCircle2f(90 + xEye, yEye, 7);
    if (!res)
        errorAlloc();
    glDrawCircle(indx, res);

    free(res);
    res = NULL;
    free(indx);
    indx = NULL;

    glColor3ub(0xc9, 0x80, 0x24);
    glRectf(60, 90, 120, yEye);
    glColor3ub(0x37, 0x30, 0x28);
    glBegin(GL_QUADS);
    glVertex2f(83 - xEye, 90);
    glVertex2f(83 - xEye, 93);
    glVertex2f(97 + xEye, 93);
    glVertex2f(97 + xEye, 90);
    glEnd();
    glFlush();
}

void    reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 180, 0, 180, -1, 1);
}

int     main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(200, 200);
    glutInitWindowPosition(600, 600);
    glutCreateWindow("OpenGL funny face");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return (0);
}
