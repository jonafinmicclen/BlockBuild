#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "RenderedObject.h"
#include "PhysicsObject.h"

class CubeBlock : public RenderedObject, public PhysicsObject{
public:

	std::vector<char> defaultFaceOrder = { 'F','B','L','R','T','D' };	// Index of letter is index of face when use auto set faces, unfortunately T and D are flipped

	void setTexturePos(const std::pair<float, float> position);
	void setVertexAndCoords();
	void setAFaceUV(const std::pair<char, std::vector<glm::vec2>> faceAndCoords);	// Adds a face char:{F,B,L,R,T,D} to the cube with uv coordinates vec2
	void setAllCornersFromTopLeft(const glm::vec2 corner);	//Sets the current texture coordinates to match the 16x16 size, not the actual texture 
	void setAllFacesUV(std::vector<glm::vec2> allCornersCoords);
	void rotateFaceACW(int surfaceIndex); //Rotates the texture of a surface by its index Anti-Clockwise
	void rotateFaceCW(int surfaceIndex); //Rotates the texture of a surface by its index Clockwise

	// Finds the collision point and normal of a rays collision with the cube from origin with incident rayVec
	std::pair<glm::vec3, glm::vec3> getCollisionPointAndNormal(const glm::vec3 rayOrigin, const glm::vec3 rayVec, const glm::vec3 cubePos);

	glm::vec2 bottomLeft;
	glm::vec2 topRight;
	glm::vec2 topLeft;
	glm::vec2 bottomRight;
	std::vector<glm::vec2> allCornersCoords;

	CubeBlock();

};

#endif // CUBEBLOCK_H
