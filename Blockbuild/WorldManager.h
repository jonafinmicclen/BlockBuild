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
#include "PerlinNoise.h"
#include "DirtBlock.h"
#include "WoodBlock.h"
#include "LeafBlock.h"
#include "CobblestoneBlock.h"
#include <list>
#include "UnboundEntity.h"
#include <random>

class WorldManager {
public:
	WorldManager();

	static const int worldHeight = 512;		//MUST be mulitple of 16
	static const int worldLength = 512;		//Must be multiple of 16 for the optimisation
	static const int renderDistance = 8;	//Meassured in chunks

	int treeHeight = 10;
	int leafRadius = 6;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> distribution;

	bool updatedLastFrame;
	std::vector<glm::ivec2> chunksToUpdate;

	std::vector<CubeBlock*> blocks;
	std::vector<UnboundEntity*> entities;
	int8_t world[worldLength][worldHeight][worldLength];		// 8-bit int for mem usage
	int8_t forceField[worldLength][worldHeight][worldLength];
	GLuint worldDisplayList;
	GLuint chunksDisplayList[worldLength/16][worldLength/16];

	std::vector<glm::ivec2> getNeighbouringPosition(const glm::ivec2 position);

	bool posOutOfBounds(const glm::ivec3 pos);		// Returns true if given coordinate is out of bounds

	int getNumOfBlocks();		// Returns number of blocks in the world

	void loadBlocks();		// Initialises block properties in memory
	void deleteBlocks();

	void explosion(const glm::ivec3 position);

	void placeBlock(const std::pair<glm::vec3, int> positionAndBlockNo);
	void generateFlatland();				// Generates a flat land enviroment in current world
	void generateWorld();

	void destroyBlock(const glm::ivec3 position);		// Does not test for out of bounds
	void replaceBlock(const std::pair<glm::ivec3, int> positionAndBlockNo);

	void loadEntity();

	// Render functions
	void drawWorld();
	void createDisplayList();
	void drawWorldUsingDisplayList();
	void drawWorldOptimised(const glm::vec2 playerPosition);
	void generateChunkDisplayList(const glm::ivec2 chunkPosition);
	void generateAllChunksDisplayLists();
	void drawWorldUsingChunksDisplayLists(const glm::vec2 playerPosition);
	void generateTree(const glm::ivec3 position);
	std::vector<int> getNeigbouringBlocks(const glm::ivec3 position);
	bool neighbourHasOpacity(const glm::ivec3 position);
	void generateBubble(const glm::ivec3 position);

};

#endif // WORLDMANAGER_H
