#include "Main.h"

CubeBlock testCubeObject;
Camera userCamera;

void renderLoop() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Draw shit and camera shit
    userCamera.autoLookAt();
    testCubeObject.draw();

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

    //Update shit
    userCamera.update();

    glutTimerFunc(16, physicsLoop, 0);  // 60 frames per second
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Moving 3D Objects");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(renderLoop);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, physicsLoop, 0);  // Initial call to update after 25 milliseconds

    glutMainLoop();
    return 0;
}
