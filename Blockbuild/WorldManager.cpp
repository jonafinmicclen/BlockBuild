#include "WorldManager.h"

WorldManager::WorldManager() {

    //Set default values in world array
    for (int i = 0; i < worldLength; ++i) {
        for (int j = 0; j < worldLength; ++j) {
            for (int k = 0; k < worldHeight; ++k) {
                world[i][j][k] = -1;
            }
        }
    }

	WorldManager::loadBlocks();
    std::cout << "[World Manager]:Blocks loaded.\n";

}

void WorldManager::placeBlock(const glm::vec3 position) {
    // Round each component of the vector
    glm::ivec3 realPosition(
        std::round(position.x),
        std::round(position.y),
        std::round(position.z)
    );

    // Check if the rounded position is within the bounds of your world
    if (realPosition.x >= 0 && realPosition.x < worldLength &&
        realPosition.y >= 0 && realPosition.y < worldLength &&
        realPosition.z >= 0 && realPosition.z < worldHeight) {

        if (world[realPosition.x][realPosition.y][realPosition.z] == -1) {
            // Place the block at the rounded position
            world[realPosition.x][realPosition.y][realPosition.z] = 0;
        }
        else {
            std::cout << "[WorldManager]:Player attempted to place block in non-empty location.\n";
        }
    }
    else {
        // Handle out-of-bounds case, if needed
        std::cerr << "[WorldManager]:Error: Attempted to place block out of bounds." << std::endl;
    }
}

void WorldManager::loadBlocks() {

	//No blocks yet
	blocks.push_back(new CubeBlock());	//Index 0 in cubes

    std::vector<CubeBlock> objList;

}

void WorldManager::deleteBlocks() {

	// Clean up: delete instances from the vector
	for (auto& element : blocks) {
		delete element;
	}

}

void WorldManager::drawWorld() {

    // Accessing each block in world
    for (int x = 0; x < worldLength; ++x) {
        for (int y = 0; y < worldLength; ++y) {
            for (int z = 0; z < worldHeight; ++z) {

                //Draws block at its index
                int blockInPlace = world[x][y][z];
                if (blockInPlace != -1) {
                    blocks[blockInPlace]->draw({ x, y, z });
                }
            }
        }
    }
}