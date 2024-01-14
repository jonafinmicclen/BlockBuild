#include "Main.h"

// INIT TEST VAR
float cameraRotationAngle = 0.0f;
float cameraRotationSpeed = 1.0f;

CubeBlock testCubeObject;

void renderLoop() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Update camera rotation
    cameraRotationAngle += 0.01 * cameraRotationSpeed;  // Adjust the multiplication factor for rotation speed

    gluLookAt(5.0 * sin(cameraRotationAngle), 0.0, 5.0 * cos(cameraRotationAngle),  // Updated camera position
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    //Draw shit here
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
