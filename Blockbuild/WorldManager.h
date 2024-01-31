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
#include "BlockModelLoader.h"
#include <random>

class WorldManager {
protected:
	static const int worldHeight = 512;		//MUST be mulitple of 16
	static const int worldLength = 128;		//Must be multiple of 16 for the optimisation
	static const int renderDistance = 8;	//Meassured in chunks

	// Also effect explosion size should change
	int treeHeight = 10;
	int leafRadius = 6;

	// Random number generation
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> distribution;

	// Keeps track of when to redraw areas of worlds
	bool updatedLastFrame;									// Only initialy used	
	std::vector<glm::ivec2> chunksToUpdate;

	// Instances of objects in world
	std::vector<CubeBlock*> blocks;
	std::vector<UnboundEntity*> entities;

	// Model loader for in game structures
	BlockModelLoader blockModelLoader = BlockModelLoader();

	// Stores world info, active forces, block positions
	int8_t world[worldLength][worldHeight][worldLength];	
	int8_t forceField[worldLength][worldHeight][worldLength];

	// World chunks display list
	GLuint chunksDisplayList[worldLength / 16][worldLength / 16];
	GLuint columnDisplayLists[worldLength][worldLength];

public:
	WorldManager();

	// Utility
	bool posOutOfBounds(const glm::ivec3 pos);											// Returns true if given coordinate is out of bounds
	int getNumOfBlocks();																// Returns number of blocks in the world
	bool neighbourHasOpacity(const glm::ivec3 position);
	std::vector<glm::ivec2> getNeighbourPositions_X_Z(const glm::ivec2 position);		// Returns position of neighbours on x,z but not y
	std::vector<int> getNeigbouringBlocks(const glm::ivec3 position);					// Returns neighbours (x,y,z)
	int getBlockAtPos(const glm::ivec3 pos);

	// Initialisation
	void loadBlocks();	
	void deleteBlocks();
	void loadEntity();

	// Updates
	void updateAll();

	// In game actions
	void explosion(const glm::ivec3 position);											// Destroys blocks in radius treeRadius
	void placeBlock(const std::pair<glm::vec3, int> positionAndBlockNo);				// Places block, checks if out of bounds and not already occupied
	void destroyBlock(const glm::ivec3 position);										// Destroys block, checks if out of bounds
	void replaceBlock(const std::pair<glm::ivec3, int> positionAndBlockNo);				// Replaces block, checks if out of bounds
	void moveProjectileToLocation(const glm::vec3 position);
	void createProjectileAtLocation(const glm::vec3 position);

	// World generation
	void generateFlatland();															// Generates a flat land
	void generateWorld();																// Generates a hilly world
	void generateBubble(const glm::ivec3 position);										// Creates a bubble
	void generateTree(const glm::ivec3 position);										// Creates a tree

	// Render functions
	void drawWorldOptimised(const glm::vec2 playerPosition);							//Automatically selects optimal functions to use to draw world and handles updates
	void generateChunkDisplayList(const glm::ivec2 chunkPosition);						// Generates chunk display list for chunk at position (x,z)
	void generateAllChunksDisplayLists();												// Automatically generates display lists for all chunks
	void drawWorldUsingChunksDisplayLists(const glm::vec2 playerPosition);				// Draws all chunk display lists
	void generateColumnDisplayList(const glm::ivec2 position);

};

#endif // WORLDMANAGER_H
