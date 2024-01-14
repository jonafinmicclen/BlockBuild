#include "Main.h"

//Testing object
RenderedObject myObject;

void renderLoop() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 5.0, //Camera perspective
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    //glTranslatef(cubePositionX, 0.0, 0.0);
    //glRotatef(angleX, 1.0, 0.0, 0.0);
    myObject.draw();

    glutWireCube(1.0);

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

    //Test
    // Add vertices and surfaces to your RenderedObject
    myObject.addVertex(glm::vec3(-0.5, -0.5, 0.0));
    myObject.addVertex(glm::vec3(0.5, -0.5, 0.0));
    myObject.addVertex(glm::vec3(0.5, 0.5, 0.0));
    myObject.addVertex(glm::vec3(-0.5, 0.5, 0.0));

    // Define a surface using indices of the vertices
    std::vector<int> quadIndices = { 0, 1, 2, 3 };
    myObject.addSurface(quadIndices);

    glutDisplayFunc(renderLoop);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, physicsLoop, 0);  // Initial call to update after 25 milliseconds

    glutMainLoop();
    return 0;
}
