#include "Main.h"

float MOUSE_SENSITIVITY = 0.001f;

CubeBlock testCubeObject = CubeBlock({ 0,0,0 });
std::vector<CubeBlock> objList;
Camera userCamera;
InputHandler inputs;

void renderLoop() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Draw shit and camera shit
    userCamera.autoLookAt();
    testCubeObject.draw();

    for (auto& objToDraw : objList) {
        objToDraw.draw();
    }

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
}

void physicsLoop(int value) {

    glutPostRedisplay();

    // Handle received inputs from handler

    // Keyboard Inputs
    auto pressed = inputs.getPressed();
    for (const auto& input : pressed) {
        switch (input) {
        case 'W':
            userCamera.moveRelativeAmbulate(0.1f);
            break;
        case 'S':
            userCamera.moveRelativeAmbulate(-0.1f);
            break;
        case 'A':
            userCamera.moveRelativeStrafe(-0.1f);
            break;
        case 'D':
            userCamera.moveRelativeStrafe(0.1f);
            break;
        case 'T':
            objList.push_back(CubeBlock({userCamera.position}));
            break;
        case 'Y':
            break;
        }
    }

    // Mouse inputs
    glm::vec2 mouseVec = inputs.getMouseMovement();
    float length = glm::length(mouseVec);
    if (length != 0) {
        mouseVec /= length;
        userCamera.rotateLook(MOUSE_SENSITIVITY * length, glm::vec3(mouseVec.y, mouseVec.x, 0));
    }

    //Update shit
    userCamera.update();

    glutTimerFunc(16, physicsLoop, 0);  // 60 frames per second
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("BlockBuild");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(renderLoop);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, physicsLoop, 0);  // Initial call to update after 25 milliseconds

    glutMainLoop();
    return 0;
}
