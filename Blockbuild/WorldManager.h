#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "CubeBlock.h"
#include "GravelBlock.h"

class WorldManager {
public:
	WorldManager();

	static const int worldHeight = 10;
	static const int worldLength = 10;

	std::vector<CubeBlock*> blocks;
	int world[worldLength][worldLength][worldHeight];

	void loadBlocks();
	void deleteBlocks();
	void drawWorld();
	void placeBlock(const glm::vec3 position);
};

#endif // WORLDMANAGER_H
