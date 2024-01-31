#ifndef UNBOUNDENTITY_H
#define UNBOUNDENTITY_H

#include <glm/glm.hpp>
#include <GL/glut.h>
#include <iostream>

class UnboundEntity
{
public:
	UnboundEntity();

	// Calculation
	void reflectVelocity(const glm::vec3 normalOfColision);		// Applies a reflection to the velocity
	void applyForceTick(const glm::vec3 forceVector);			// Applies a force and calculates new velocity after ticklength
	void updateTick();											// Updates position based on velocity

	// Utility
	float getSpeed();											// Returns current speed
	glm::vec3 getColisionCoords(const glm::vec3& planeNormal,
		const glm::vec3& planePosition);						// Returns position of colision given block coordinate
	void handleCollision(const glm::vec3& planeNormal,
		const glm::vec3& planePosition);						// Calculates new position and updatees velocity
	glm::vec3 getNextPosition();
	bool alive = true;

	// Rendering
	void draw();
	glm::vec3 position;
	glm::vec3 velocity;

protected:

	
	float mass;
};

#endif // UNBOUNDENTITY_H
