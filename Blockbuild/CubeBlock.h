#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "RenderedObject.h"
#include "PhysicsObject.h"

class CubeBlock : public RenderedObject, public PhysicsObject{
public:
	CubeBlock(glm::vec3 newPosition);
};

#endif // CUBEBLOCK_H
