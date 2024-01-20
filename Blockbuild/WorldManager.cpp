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

int WorldManager::getNumOfBlocks() {
    return blocks.size();
}

void WorldManager::placeBlock(const std::pair<glm::vec3, int> positionAndBlockNo) {
    // Round each component of the vector
    auto position = positionAndBlockNo.first;
    auto blockNo = positionAndBlockNo.second;

    glm::ivec3 realPosition(
        std::round(position.x),
        std::round(position.y),
        std::round(position.z)
    );

    // Check if the rounded position is within the bounds of world
    if (realPosition.x >= 0 && realPosition.x < worldLength &&
        realPosition.y >= 0 && realPosition.y < worldLength &&
        realPosition.z >= 0 && realPosition.z < worldHeight) {

        if (world[realPosition.x][realPosition.y][realPosition.z] == -1) {
            // Place the block at the rounded position
            world[realPosition.x][realPosition.y][realPosition.z] = blockNo;
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

	// Blocks in game
	blocks.push_back(new GravelBlock());	//Index 0 in cubes
    blocks.push_back(new StoneBlock());
    blocks.push_back(new BedrockBlock());
    blocks.push_back(new WoodplanksBlock());
    blocks.push_back(new GlassBlock());
    blocks.push_back(new DiamondOreBlock());

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

void WorldManager::generateWorld() {

    for (int x = 0; x < worldLength; ++x) {
        for (int z = 0; z < worldLength; ++z) {


            int height = round(sin(x*z/69)*20);
            std::cout << height;

            for (int y = 0; y < height; ++y) {
                placeBlock({ { x,y ,z }, 1 });
            }
        }
    }
}