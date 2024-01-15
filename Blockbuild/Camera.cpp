#include "Camera.h"

void Camera::autoLookAt(){
    gluLookAt(
        position.x,     position.y,     position.z,
        target.x,       target.y,       target.z,
        up.x,           up.y,           up.z);
}

void Camera::rotateLook(float angle, glm::vec3 axis) {

    // Quat rotator logic
    glm::vec3 relativeLook = target - position;
    glm::quat rotation = glm::angleAxis(angle, axis);
    glm::vec3 rotatedRelativeLook = rotation * relativeLook;
    glm::vec3 newTarget = rotatedRelativeLook + position;
    target = newTarget;
}

void Camera::moveRelativeAmbulate(float magnitude) {

    glm::vec3 relativeLook = target - position;
    glm::vec3 normalisedRelativeLook = glm::normalize(relativeLook);
    position += normalisedRelativeLook * magnitude;
    target += normalisedRelativeLook * magnitude;
}

void Camera::moveRelativeStrafe(float magnitude) {

    glm::vec3 relativeLook = target - position;
    glm::vec3 rightVector = glm::cross(relativeLook, up);
    glm::vec3 strafeVector = glm::normalize(rightVector);
    position += strafeVector * magnitude;
    target += strafeVector * magnitude;
}


void Camera::update()  { 
    PhysicsObject::update();

    // Update logic here

}

//None yet