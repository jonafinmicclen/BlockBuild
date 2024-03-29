#include "Camera.h"

void Camera::autoLookAt(){
    gluLookAt(
        position.x,     position.y,     position.z,
        target.x,       target.y,       target.z,
        up.x,           up.y,           up.z);
}

void Camera::draw() {

    glPushMatrix();
    GLUquadric* quad;
    quad = gluNewQuadric();
    glTranslatef(target.x, target.y, target.z);
    gluSphere(quad, 0.05, 10, 10);
    glPopMatrix();
}

void Camera::rotateLookByDMXY(glm::vec2 mouseDelta) {

    // Sensitivity factoring
    mouseDelta.y /= -600;   
    mouseDelta.x /= 180;
    
    // Calcuates new target after rotation
    glm::vec3 rotationAxis = glm::cross(up, target - position);
    glm::quat rotationQuat = glm::angleAxis(mouseDelta.x, up)
        * glm::angleAxis(mouseDelta.y, rotationAxis);
    auto newTarget = position + glm::rotate(rotationQuat, target - position);

    // Maintain distance to target
    auto targetDistance = glm::distance(newTarget, position);
    std::cout << "[Camera]:Current distance to target :" << targetDistance << ".\n";
    auto distanceRatio = distanceToTargetGoal / targetDistance;
    newTarget = position + (newTarget - position) * distanceRatio;

    // Cant look directly up or down
    auto lookUpDelta = abs(newTarget.y - position.y);
    if (lookUpDelta <= maxLookUpDelta) {
        target = newTarget;
    }
    else {
        if (newTarget.y > target.y) {
            target = { newTarget.x, position.y + maxLookUpDelta, newTarget.z };
        }
        else {
            target = { newTarget.x, position.y - maxLookUpDelta, newTarget.z };
        }
    }
}

void Camera::rotateLook(float angle, glm::vec3 axis) {
    // Rotate the target around the camera position
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    target = glm::vec3(rotationMatrix * glm::vec4(target - position, 1.0f)) + position;
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

Camera::Camera() {
 
}


void Camera::update()  { 
    PhysicsObject::update();

    // Update logic here

}

//None yet