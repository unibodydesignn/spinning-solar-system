#include <iostream>
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

    camera = new Camera(glm::vec3(0.0f, 0.0f, 1.0f));
    lastX = 1920 / 2;
    lastY = 1080 / 2;
    firstMouse = false;
    deltaTime = 0.0f;
    lastFrame = 0.0f;

}

void doModelTranslation(glm::mat4& modelMatrix) {
    sun->calculateTransformation(modelMatrix);
}

void initializeSpaceLayout(void) {

    glUseProgram(sun->shader->getProgramID());

    glEnable( GL_DEPTH_TEST );
    glViewport(0, 0, WW, WH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 1920, 0, 1080, 0, 1000);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    mvp = glm::mat4(1.0f);
}

void displaySystem() {

    glEnable( GL_DEPTH_TEST );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    deltaTime = 0.5;

    doModelTranslation(model);
    view  = camera->GetViewMatrix();
    projection = glm::perspective(camera->GetZoom(), (float) 1920 / (float) 1080, 0.1f, 1000.0f);
    mvp = projection * view * model;
    
    sun->shader->EditMatrix4("mvp", mvp);
    glUseProgram(sun->shader->getProgramID());
    
    sun->draw();

    glutSwapBuffers();
}

void controlSpaceWithMouse(int btn, int st, int xPos, int yPos) {
    if (btn == GLUT_LEFT_BUTTON && st == GLUT_DOWN) {
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

        //printf("MOUSE X : %d   Y : %d \n", xPos, yPos);
    }
}

void keyboardInput(unsigned char key, int x, int y) {
    if( key == 'W' ) {
        camera->ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if( key == 'S'  ) {
        camera->ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if( key == 'A' ) {
        camera->ProcessKeyboard( LEFT, deltaTime );
    }
    
    if( key == 'D' ) {
        camera->ProcessKeyboard( RIGHT, deltaTime );
    }
}

void scrollCallback(int xPos, int yPos, int zPos) {
    printf("x %d y %d z %d \n", xPos, yPos, zPos);
    camera->ProcessMouseScroll( zPos );
}

/**
 *
 * This is where magic happencls.
 * Magic of glutMainLoop.
 *
 * */
int main(int argc, char** argv) {

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitDisplayMode(GLUT_3_2_CORE_PROFILE);
   glutInitWindowSize(WW, WH);
   glutInitWindowPosition(0,0);
   glutCreateWindow("Solar System");

   init();

   glewExperimental = GL_TRUE;
    glewInit();

   initializeSpaceLayout();
   glutMouseFunc(controlSpaceWithMouse);
   glutDisplayFunc(displaySystem);
   glutSpaceballMotionFunc(scrollCallback);
   glutKeyboardFunc(keyboardInput);
   glutMainLoop();
}
