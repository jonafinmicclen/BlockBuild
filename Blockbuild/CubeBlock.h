#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "RenderedObject.h"
#include "PhysicsObject.h"

class CubeBlock : public RenderedObject, public PhysicsObject{
public:
	std::pair<float, float> texturePos;
	CubeBlock();

};

#endif // CUBEBLOCK_H
