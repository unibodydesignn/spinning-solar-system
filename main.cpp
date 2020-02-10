#include <iostream>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

#include "Angel.h"
#include "CheckError.h"

#include "sun.h"

#define WW 1920
#define WH 1080

Sun *sun;

void init() {
    sun = new Sun();
    sun->init();
}

void initializeSpaceLayout(void) {
    glViewport(0, 0, WW, WH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)WW, 0.0, (GLdouble)WH);

    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void displaySystem() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sun->draw();
    glutSwapBuffers();
}

void controlSpaceWithMouse(int btn, int state, int x, int y) {
    printf("Mouse coordinates when button pressed : %d %d\n",x, y);
}

void keyboardInput(unsigned char key, int x, int y) {
    printf("Mouse coordinates when button pressed : %d %d\n",x, y);
}

/**
 *
 * This is where magic happens.
 * Magic of glutMainLoop.
 *
 * */
int main(int argc, char** argv) {

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH |GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(WW, WH);
   glutInitWindowPosition(0,0);
   glutCreateWindow("Solar System");
   initializeSpaceLayout();
   glutMouseFunc(controlSpaceWithMouse);
   glutDisplayFunc(displaySystem);
   glutKeyboardFunc(keyboardInput);

   glutMainLoop();
}
