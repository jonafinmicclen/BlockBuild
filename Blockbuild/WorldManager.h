#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "CubeBlock.h"
#include "GravelBlock.h"
#include "StoneBlock.h"
#include "BedrockBlock.h"
#include "WoodplanksBlock.h"
#include "GlassBlock.h"
#include "DiamondOreBlock.h"

class WorldManager {
public:
	WorldManager();

	static const int worldHeight = 30;
	static const int worldLength = 20;

	std::vector<CubeBlock*> blocks;
	int world[worldLength][worldLength][worldHeight];

	int getNumOfBlocks();
	void loadBlocks();
	void deleteBlocks();
	void drawWorld();
	void placeBlock(const std::pair<glm::vec3, int> positionAndBlockNo);
	void generateWorld();
};

#endif // WORLDMANAGER_H
