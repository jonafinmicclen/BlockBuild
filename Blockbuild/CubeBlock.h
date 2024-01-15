#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "RenderedObject.h"
#include "PhysicsObject.h"

class CubeBlock : public RenderedObject, public PhysicsObject{
public:
	CubeBlock(glm::vec3 newPosition);
	const char* textureFilePath = "C:/Users/jonat/Music/new/terrain.png";
};

#endif // CUBEBLOCK_H
