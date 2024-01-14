#include "Camera.h"

void Camera::autoLookAt(){
    gluLookAt(
        position.x,     position.y,     position.z,
        target.x,       target.y,       target.z,
        up.x,           up.y,           up.z);
}

void Camera::update()  { 
    PhysicsObject::update();

    float camX = sin(existanceTicks/6) * 5;
    float camZ = cos(existanceTicks/6) * 5;
    position.x = camX;
    position.z = camZ;
}

//None yet