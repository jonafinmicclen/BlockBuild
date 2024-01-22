#include "WorldManager.h"

WorldManager::WorldManager() {

    // Seed the random number generator (use a different seed for actual randomness)
    std::random_device rd;
    std::mt19937 gen(rd());



    //Set default values in world array
    for (int x = 0; x < worldLength; ++x) {
        for (int y = 0; y < worldHeight; ++y) {
            for (int z = 0; z < worldLength; ++z) {
                world[x][y][z] = -1;
            }
        }
    }

	WorldManager::loadBlocks();
    updatedLastFrame = true;
    std::cout << "[World Manager]:Blocks loaded.\n";

}

int WorldManager::getNumOfBlocks() {
    return blocks.size();
}

void WorldManager::replaceBlock(const std::pair<glm::ivec3, int> positionAndBlockNo) {

    // Round each component of the vector
    auto realPosition = positionAndBlockNo.first;
    auto blockNo = positionAndBlockNo.second;

    // Check if the rounded position is within the bounds of world
    if (realPosition.x >= 0 && realPosition.x < worldLength &&
        realPosition.y >= 0 && realPosition.y < worldHeight &&
        realPosition.z >= 0 && realPosition.z < worldLength) {

        world[realPosition.x][realPosition.y][realPosition.z] = blockNo;
    }

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
        realPosition.y >= 0 && realPosition.y < worldHeight &&
        realPosition.z >= 0 && realPosition.z < worldLength) {

        if (world[realPosition.x][realPosition.y][realPosition.z] == -1) {
            // Place the block at the rounded position
            world[realPosition.x][realPosition.y][realPosition.z] = blockNo;
            // Keep track of when to update chunks
            chunksToUpdate.push_back({ realPosition.x/16,realPosition.z/16 });
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
    blocks.push_back(new ChestBlock());
    blocks.push_back(new GrassBlock());
    blocks.push_back(new TntBlock());
    blocks.push_back(new DirtBlock());
    blocks.push_back(new WoodBlock());
    blocks.push_back(new LeafBlock());

}

void WorldManager::generateFlatland() {
    for (int x = 0; x < worldLength; ++x) {
        for (int z = 0; z < worldLength; ++z) {
            for (int y = 0; y < 6; ++y) {
                if (y == 0) {
                    world[x][y][z] = 2;
                }
                if (y>0 && y<5) {
                    world[x][y][z] = 1;
                }
                if (y == 5) {
                    world[x][y][z] = 6;
                }
            }
        }
    }
    updatedLastFrame = true;
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
        for (int y = 0; y < worldHeight; ++y) {
            for (int z = 0; z < worldLength; ++z) {

                //Draws block at its index
                int blockInPlace = world[x][y][z];
                if (blockInPlace != -1) {
                    blocks[blockInPlace]->draw({ x, y, z });
                }
            }
        }
    }
}

void WorldManager::drawWorldOptimised(const glm::vec2 playerPosition) {
    if (chunksToUpdate.size()>0) {
        
        for (const auto& chunkToUpdate : chunksToUpdate) {
            std::cout << "[WorldManager]:Creating chunk display list at chunk x:"<< chunkToUpdate.x<<", z:"<<chunkToUpdate.y<<".\n";
            generateChunkDisplayList({chunkToUpdate});
        }
        chunksToUpdate.clear();
    }
    drawWorldUsingChunksDisplayLists(playerPosition);
}

void WorldManager::createDisplayList() {
    worldDisplayList = glGenLists(1);
    glNewList(worldDisplayList, GL_COMPILE);

    // Accessing each block in the world
    for (int x = 0; x < worldLength; ++x) {
        for (int y = 0; y < worldHeight; ++y) {
            for (int z = 0; z < worldLength; ++z) {

                // Draws block at its index
                int blockInPlace = world[x][y][z];
                if (blockInPlace != -1) {
                    blocks[blockInPlace]->draw({ x, y, z });
                }
            }
        }
    }

    glEndList();
}

void WorldManager::drawWorldUsingChunksDisplayLists(const glm::vec2 playerPosition) {

    for (int x = 0; x < worldLength / 16; ++x) {
        for (int z = 0; z < worldLength / 16; ++z) {

            glm::vec2 chunkPos = { x,z };
            glm::vec2 relPlayerPos =  {playerPosition.x/16, playerPosition.y/16};
            int distanceToChunk = glm::length(relPlayerPos - chunkPos);
            if (distanceToChunk <= renderDistance) {
                glCallList(chunksDisplayList[x][z]);
            }

        }
    }
}

void WorldManager::generateAllChunksDisplayLists() {
    for (int x = 0; x < worldLength/16; ++x) {
        for (int z = 0; z < worldLength/16; ++z) {

            generateChunkDisplayList({ x,z });

        }
    }
}

void WorldManager::generateChunkDisplayList(const glm::ivec2 chunkPosition) {

    glDeleteLists(chunksDisplayList[chunkPosition.x][chunkPosition.y], 1);

    chunksDisplayList[chunkPosition.x][chunkPosition.y] = glGenLists(1);    //Here x and y refers to x and z as chunk doesnt have y coord
    glNewList(chunksDisplayList[chunkPosition.x][chunkPosition.y], GL_COMPILE);

    // Accessing each block in the chunk
    for (int x = chunkPosition.x * 16; x < chunkPosition.x * 16 + 16; ++x) {
        for (int z = chunkPosition.y * 16; z < chunkPosition.y * 16 + 16; ++z) {
            for (int y = worldHeight-1; y >= 0; --y) {

                // Draws block at its index
                auto& blockInPlace = world[x][y][z];
                if (blockInPlace != -1) {
                    blocks[world[x][y][z]]->draw({ x, y, z });
                    break;
                }
            }
        }
    }

    glEndList();
}

void WorldManager::drawWorldUsingDisplayList() {
    glCallList(worldDisplayList);
}

void WorldManager::generateTree(const glm::ivec3 position) {

    for (int r = 0; r <= leafRadius; r++) {
        for (float polarAngle = 0; polarAngle < 3; polarAngle += 0.1) {
            for (float azimuthalAngle = 0; azimuthalAngle < 3; azimuthalAngle += 0.1) {
                double x = leafRadius * sin(polarAngle) * cos(azimuthalAngle);
                double y = leafRadius * sin(polarAngle) * sin(azimuthalAngle);
                double z = leafRadius * cos(polarAngle);
                glm::ivec3 offset = { x,y + treeHeight - leafRadius + 1,z };
                glm::ivec3 leafPos = position + offset;
                replaceBlock({ leafPos, 10 });
            }
        }
    }
    for (int i = 0; i < treeHeight; ++i) {
        replaceBlock({ {position.x, position.y + i, position.z}, 9});
    }
}

void WorldManager::generateWorld() {

    PerlinNoise perlin;
    auto heightmap = perlin.generateHeightmap(worldLength, worldLength, 0.01, 0.01);

    for (int x = 0; x < worldLength; ++x) {
        for (int z = 0; z < worldLength; ++z) {
            auto heightOfColumn = std::floor( 40 * abs(heightmap[x][z]) + 15);
            for (int y = 0; y <= heightOfColumn; ++y) {

                if (y/heightOfColumn > 0.8) {
                    world[x][y][z] = 8;
                }
                else {
                    world[x][y][z] = 1;
                }
                if (y == heightOfColumn) {      //Randomly generate trees if y>10
                    std::uniform_int_distribution<int> distribution(0, 1000);
                    bool shouldGenTree = distribution(gen) == 1;
                    if (y > 10 && shouldGenTree) {

                        generateTree({ x,y,z });
                    }

                    world[x][y][z] = 6;
                }
                if (y == 0) {
                    world[x][y][z] = 2;
                }
            }
        }
    }
}