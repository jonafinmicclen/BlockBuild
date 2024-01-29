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

glm::vec3 UnboundEntity::getColisionCoords(const glm::vec3& planeNormal, const glm::vec3& planePosition) {
    // Calculate time of collision
    float tCollision = glm::dot((planePosition - position), planeNormal) / glm::dot(velocity, planeNormal);

    // Calculate collision point
    glm::vec3 collisionPoint = position + tCollision * velocity;

    return collisionPoint;
}

void UnboundEntity::handleCollision(const glm::vec3& planeNormal, const glm::vec3& planePosition) {
    std::cout << "[UnboundEntity]: Position and velocity before colision: P:" << position.x << ", " << position.y << ", " << position.z << "; V:" << velocity.x << ", " << velocity.y << ", " << velocity.z << ".\n";
    // Calculate time of collision
    float tCollision = glm::dot((planePosition - position), planeNormal) / glm::dot(velocity, planeNormal);

    // Calculate collision point
    glm::vec3 collisionPoint = position + tCollision * velocity;

    // Calculate distance traveled to collision point
    float distanceToCollision = glm::length(collisionPoint - position);

    // Reflect velocity
    auto preSpeed = getSpeed();
    reflectVelocity(planeNormal);
    velocity /= getSpeed() / preSpeed;

    // Update position for the remaining distance after collision
    position = collisionPoint + (1-(distanceToCollision / glm::length(velocity))) * velocity;

    std::cout << "[UnboundEntity]: Position and velocity after colision: P:" << position.x << ", " << position.y << ", " << position.z << "; V:" << velocity.x << ", " << velocity.y << ", " << velocity.z << "; collision with :" << planeNormal.x << "," << planeNormal.y << "," << planeNormal.z << ".\n";
}

glm::vec3 UnboundEntity::getNextPosition() {
    return position + velocity;
}