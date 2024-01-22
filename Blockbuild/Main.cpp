#include "Main.h"

Camera userCamera;
InputHandler inputs;
WorldManager* manager; // Declare as a pointer
PlayerManager* playerManager;

float MOVESPEED = 0.1;

void renderLoop() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enable blending for drawing on top

    // Draw shit and camera shit
    userCamera.autoLookAt();
    manager->drawWorldOptimised({userCamera.position.x, userCamera.position.z});
    userCamera.draw();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (GLfloat)width / (GLfloat)height, 0.1, 1000);
}

void physicsLoop(int value) {

    glutPostRedisplay();

    // Handle received inputs from handler

    // Keyboard Inputs
    auto pressed = inputs.getPressed();
    for (const auto& input : pressed) {
        switch (input) {
        case 'W':
            userCamera.moveRelativeAmbulate(MOVESPEED);
            break;
        case 'S':
            userCamera.moveRelativeAmbulate(-MOVESPEED);
            break;
        case 'A':
            userCamera.moveRelativeStrafe(-MOVESPEED);
            break;
        case 'D':
            userCamera.moveRelativeStrafe(MOVESPEED);
            break;
        case 'T':
            manager->placeBlock({userCamera.target, playerManager->blockInHand});
            break;
        case 'Y':
            playerManager->selectNextBlock();
            break;
        default:
            // Check if it's an integer character
            if (isdigit(input)) {
                int intValue = std::stoi(std::string(1, input));
                std::cout << "[Main]:BlockInHand set to " << intValue << ".\n";
                playerManager->blockInHand = intValue;
            }
            break;
        }
    }

    // Mouse inputs
    glm::vec2 mouseVec = inputs.getMouseMovement();
    if (glm::length(mouseVec) != 0) {
        userCamera.rotateLookByDMXY(mouseVec);
    }

    //Update shit
    playerManager->updateOnTick();
    userCamera.update();

    glutTimerFunc(16, physicsLoop, 0);  // 60 frames per second
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("BlockBuild");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    manager = new WorldManager(); // Creates world manager
    playerManager = new PlayerManager();
    playerManager->setNumOfItems(manager->getNumOfBlocks());
    manager->generateWorld();
    manager->generateAllChunksDisplayLists();

    glutDisplayFunc(renderLoop);
    glutReshapeFunc(reshape);
    // Delayed instantiation of WorldManager
    glutTimerFunc(25, [](int) {
        glutTimerFunc(25, physicsLoop, 0);  // Initial call to update after 25 milliseconds
        }, 0);

    glutMainLoop();
    return 0;
}
