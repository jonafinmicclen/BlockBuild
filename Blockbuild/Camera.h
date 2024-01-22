#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "PhysicsObject.h"

class Camera : public PhysicsObject{
public:
	Camera();

	glm::vec3 position =	{ 0,100,0 };
	glm::vec3 target =		{ 2,100,2 };
	glm::vec3 up =			{ 0,1,0 };

	void autoLookAt();
	void update();

	void draw();

	void rotateLook(float, glm::vec3);
	void moveRelativeAmbulate(float);
	void moveRelativeStrafe(float);
	void rotateLookByDMXY(glm::vec2 mouseDelta);

};
#endif // CAMERA_H
