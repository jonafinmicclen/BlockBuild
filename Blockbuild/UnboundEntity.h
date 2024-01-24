#ifndef UNBOUNDENTITY_H
#define UNBOUNDENTITY_H

#include <glm/glm.hpp>
#include <GL/glut.h>

class UnboundEntity
{
public:

	void reflectVelocity(const glm::vec3 normalOfColision);		// Applies a reflection to the velocity
	void applyForceTick(const glm::vec3 forceVector);			// Applies a force and calculates new velocity after ticklength
	void updateTick();											// Updates position based on velocity
	float getSpeed();											// Returns current speed
	void draw();
	glm::vec3 position;

protected:

	glm::vec3 velocity;
	float mass;
};

#endif // UNBOUNDENTITY_H
