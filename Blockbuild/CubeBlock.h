#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "RenderedObject.h"
#include "PhysicsObject.h"

class CubeBlock : public RenderedObject, public PhysicsObject{
public:
	
	CubeBlock();

	std::pair<float, float> texturePos;
	void setTexturePos(const std::pair<float, float> position);
	void setVertexAndCoords();

};

#endif // CUBEBLOCK_H
