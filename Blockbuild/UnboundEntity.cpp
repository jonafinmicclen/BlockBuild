#include "UnboundEntity.h"

UnboundEntity::UnboundEntity() {
    velocity = { 0.1f,-0.1f,0.1f };
    position = { 0,0,0 };
    mass = 1;
}

void UnboundEntity::reflectVelocity(const glm::vec3 normalOfCollision) {
    glm::vec3 normalizedVelocity = glm::normalize(velocity);
    glm::vec3 normalizedNormal = glm::normalize(normalOfCollision);
    velocity = normalizedVelocity - 2.0f * glm::dot(normalizedVelocity, normalizedNormal) * normalizedNormal;
}

void UnboundEntity::applyForceTick(const glm::vec3 forceVector) {
	velocity += forceVector / mass;
}

void UnboundEntity::updateTick(){
    if (position.y < -50) {
        alive = false;
    }
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
	gluSphere(quad, 0.2, 10, 10);
	glPopMatrix();
}

glm::vec3 UnboundEntity::getColisionCoords(const glm::vec3& planeNormal, const glm::vec3& planePosition) {
    // Calculate time of collision
    float tCollision = glm::dot((planePosition - position), planeNormal) / glm::dot(velocity, planeNormal);

    // Calculate collision point
    glm::vec3 collisionPoint = position + tCollision * velocity;

    return collisionPoint;
}

void UnboundEntity::handleCollision(const glm::vec3& planeNormal, const glm::vec3& collisionPosition) {

    // Reflect velocity
    auto preSpeed = getSpeed();
    reflectVelocity(glm::normalize(planeNormal));
    // Ensure constant speed after collision
    velocity /= getSpeed() / preSpeed;
    // Offset position to match actual position after frame
    auto remainingProportionOfVelocity = (preSpeed - glm::distance(collisionPosition, position)) / preSpeed;
    position = collisionPosition + velocity * remainingProportionOfVelocity;
}

glm::vec3 UnboundEntity::getNextPosition() {
    return position + velocity;
}