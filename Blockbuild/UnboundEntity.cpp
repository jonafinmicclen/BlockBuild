#include "UnboundEntity.h"


void UnboundEntity::reflectVelocity(const glm::vec3 normalOfColision) {
	velocity = velocity - 2.0f * glm::dot(velocity, normalOfColision) * velocity;
}

void UnboundEntity::applyForceTick(const glm::vec3 forceVector) {
	velocity += forceVector / mass;
}

void UnboundEntity::updateTick(){
	position += velocity;
}

float UnboundEntity::getSpeed() {
	return glm::length(velocity);
}

void UnboundEntity::draw() {
	glPushMatrix();
	GLUquadric* quad;
	quad = gluNewQuadric();
	glTranslatef(position.x, position.y, position.z);
	gluSphere(quad, 0.05, 10, 10);
	glPopMatrix();
}