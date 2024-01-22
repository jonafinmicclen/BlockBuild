#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "CubeBlock.h"
#include "GravelBlock.h"
#include "StoneBlock.h"
#include "BedrockBlock.h"
#include "WoodplanksBlock.h"
#include "GlassBlock.h"
#include "ChestBlock.h"
#include "GrassBlock.h"
#include "TntBlock.h"

class WorldManager {
public:
	WorldManager();

	static const int worldHeight = 32;		//MUST be mulitple of 16
	static const int worldLength = 640;		//Must be multiple of 16 for the optimisation
	static const int renderDistance = 3;	//Meassured in chunks

	bool updatedLastFrame;
	std::vector<glm::vec2> chunksToUpdate;

	std::vector<CubeBlock*> blocks;
	int world[worldLength][worldHeight][worldLength];
	GLuint worldDisplayList;
	GLuint chunksDisplayList[worldLength/16][worldLength/16];

	int getNumOfBlocks();

	void loadBlocks();
	void deleteBlocks();
	void drawWorld();
	void placeBlock(const std::pair<glm::vec3, int> positionAndBlockNo);
	void generateFlatland();				// Generates a flat land enviroment in current world
	void createDisplayList();
	void drawWorldUsingDisplayList();
	void drawWorldOptimised(const glm::vec2 playerPosition);
	void generateChunkDisplayList(const glm::ivec2 chunkPosition);
	void generateAllChunksDisplayLists();
	void drawWorldUsingChunksDisplayLists(const glm::vec2 playerPosition);
};

#endif // WORLDMANAGER_H
