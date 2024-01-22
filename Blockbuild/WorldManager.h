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
#include <random>

class WorldManager {
public:
	WorldManager();

	static const int worldHeight = 64;		//MUST be mulitple of 16
	static const int worldLength = 640;		//Must be multiple of 16 for the optimisation
	static const int renderDistance = 10;	//Meassured in chunks

	static const int treeHeight = 10;
	static const int leafRadius = 6;

	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> distribution;

	bool updatedLastFrame;
	std::vector<glm::vec2> chunksToUpdate;

	std::vector<CubeBlock*> blocks;
	int world[worldLength][worldHeight][worldLength];
	GLuint worldDisplayList;
	GLuint chunksDisplayList[worldLength/16][worldLength/16];

	int getNumOfBlocks();

	void loadBlocks();
	void deleteBlocks();

	void placeBlock(const std::pair<glm::vec3, int> positionAndBlockNo);
	void generateFlatland();				// Generates a flat land enviroment in current world
	void generateWorld();

	void replaceBlock(const std::pair<glm::ivec3, int> positionAndBlockNo);

	// Render functions
	void drawWorld();
	void createDisplayList();
	void drawWorldUsingDisplayList();
	void drawWorldOptimised(const glm::vec2 playerPosition);
	void generateChunkDisplayList(const glm::ivec2 chunkPosition);
	void generateAllChunksDisplayLists();
	void drawWorldUsingChunksDisplayLists(const glm::vec2 playerPosition);
	void generateTree(const glm::ivec3 position);
	void getNeigbouringBlocks(const glm::ivec3 position);
};

#endif // WORLDMANAGER_H
