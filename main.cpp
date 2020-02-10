#include <iostream>
#include <GLUT/glut.h>
#include <GLFW/glfw3.h>

#include "Angel.h"
#include "CheckError.h"

#include "Camera.h"
#include "sun.h"

#define WW 1920
#define WH 1080

Sun *sun;
GLfloat lastX;
GLfloat lastY;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool keys[1024];
bool firstMouse = false;
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, -10.0f));
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;
glm::mat4 mvp;

float unit = 3.0f;
float movementSpeed = 0.5f;
float velocity;

void init() {
    sun = new Sun();
    sun->init();

    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    lastX = 1920 / 2;
    lastY = 1080 / 2;
    firstMouse = false;
    deltaTime = 0.0f;
    lastFrame = 0.0f;

}

void initializeSpaceLayout(void) {
    glViewport(0, 0, WW, WH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 1920, 0, 1080, 0, 1000);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_DEPTH_TEST );
    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    mvp = glm::mat4(1.0f);
}

void displaySystem() {

    deltaTime = 0.5;

    view  = camera->GetViewMatrix();
    projection = glm::perspective(camera->GetZoom(), (float) 1920 / (float) 1080, 0.1f, 1000.0f);
    mvp = projection * view * model;

    sun->shader->EditMatrix4("mvp", mvp);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sun->draw();
    glutSwapBuffers();
}

void controlSpaceWithMouse(int xPos, int yPos) {
    if( firstMouse )
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }
        
        GLfloat xOffset = xPos - lastX;
        GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
        
        lastX = xPos;
        lastY = yPos;
        
        camera->ProcessMouseMovement( xOffset, yOffset );

        printf("MOUSE X : %d   Y : %d \n", xPos, yPos);

}

void keyboardInput(unsigned char key, int x, int y) {
    printf("Mouse coordinates when button pressed : %d %d\n",x, y);
}

void scrollCallback(int xPos, int yPos, int zPos) {
    camera->ProcessMouseScroll( yPos );
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
   glutInitDisplayMode(GLUT_3_2_CORE_PROFILE);
   glutInitWindowSize(WW, WH);
   glutInitWindowPosition(0,0);
   glutCreateWindow("Solar System");

   init();

   initializeSpaceLayout();
   glutPassiveMotionFunc(controlSpaceWithMouse);
   glutDisplayFunc(displaySystem);
   glutSpaceballMotionFunc(scrollCallback);
   glutKeyboardFunc(keyboardInput);

   glutMainLoop();
}
