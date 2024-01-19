#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "RenderedObject.h"
#include "PhysicsObject.h"

class CubeBlock : public RenderedObject, public PhysicsObject{
public:
	std::pair<float, float> texturePos = { 0.0f, 0.0f };	//Specifies which texture in terrain.png

	CubeBlock();

};

#endif // CUBEBLOCK_H
