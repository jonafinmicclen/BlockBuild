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

    //Set default values in force field array
    for (int x = 0; x < worldLength; ++x) {
        for (int y = 0; y < worldHeight; ++y) {
            for (int z = 0; z < worldLength; ++z) {
                forceField[x][y][z] = 0.0f;
            }
        }
    }

    loadEntity();
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
    if (!posOutOfBounds(realPosition)) {

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

void WorldManager::loadEntity() {
    entities.push_back(new UnboundEntity());
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
    blocks.push_back(new CobblestoneBlock());

    for (auto& block : blocks) {
        block->generateDisplayList();
    }

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

void WorldManager::drawWorldOptimised(const glm::vec2 playerPosition) {
    if (chunksToUpdate.size()>0) {
        
        // Update chunks
        for (const auto& chunkToUpdate : chunksToUpdate) {
            for (const auto& extraChunkToUpdate : getNeighbourPositions_X_Z(chunkToUpdate)) {
                std::cout << "[WorldManager]:Creating chunk display list at chunk x:" << extraChunkToUpdate.x << ", z:" << extraChunkToUpdate.y << ".\n";
                generateChunkDisplayList({ extraChunkToUpdate });
            }
        }
        chunksToUpdate.clear();
    }
    // Draw chunks
    entities[0]->draw();
    drawWorldUsingChunksDisplayLists(playerPosition);
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

std::vector<glm::ivec2> WorldManager::getNeighbourPositions_X_Z(const glm::ivec2 position) {

    std::vector<glm::ivec2> neighbourCoords;
    glm::ivec2 offsetXs = { 1,0 };
    glm::ivec2 offsetZs = { 0,1 };

    neighbourCoords.push_back(position + offsetXs);
    neighbourCoords.push_back(position - offsetXs);
    neighbourCoords.push_back(position + offsetZs);
    neighbourCoords.push_back(position - offsetZs);
    neighbourCoords.push_back(position);

    return neighbourCoords;

}

std::vector<int> WorldManager::getNeigbouringBlocks(const glm::ivec3 position) {

    glm::ivec3 neighbourCoords[6];
    glm::ivec3 offsetXs = { 1,0,0 };
    glm::ivec3 offsetYs = { 0,1,0 };
    glm::ivec3 offsetZs = { 0,0,1 };

    neighbourCoords[0] = position + offsetXs;
    neighbourCoords[1] = position - offsetXs;
    neighbourCoords[2] = position + offsetZs;
    neighbourCoords[3] = position - offsetZs;
    neighbourCoords[4] = position + offsetYs;
    neighbourCoords[5] = position - offsetYs;

    std::vector<int> neigbouringBlocks;

    for (const auto& neighbour : neighbourCoords) {
        if (!posOutOfBounds(neighbour)) {
            neigbouringBlocks.push_back(world[neighbour.x][neighbour.y][neighbour.z]);
        }
    }
    return neigbouringBlocks;
}

bool WorldManager::neighbourHasOpacity(const glm::ivec3 position) {

    for (auto& block : getNeigbouringBlocks(position)) {
        if (block == -1 || block == 4) {
            return true;
        }
    }
    return false;
}

void WorldManager::generateChunkDisplayList(const glm::ivec2 chunkPosition) {

    glDeleteLists(chunksDisplayList[chunkPosition.x][chunkPosition.y], 1);

    chunksDisplayList[chunkPosition.x][chunkPosition.y] = glGenLists(1);    //Here x and y refers to x and z as chunk doesnt have y coord
    glNewList(chunksDisplayList[chunkPosition.x][chunkPosition.y], GL_COMPILE);

    // Accessing each block in the chunk
    for (int x = chunkPosition.x * 16; x < chunkPosition.x * 16 + 16; ++x) {
        for (int z = chunkPosition.y * 16; z < chunkPosition.y * 16 + 16; ++z) {

            for (int y = worldHeight-1; y >= 0; --y) {      //Top down render

                // Draws block at its index
                auto& blockInPlace = world[x][y][z];


                if (blockInPlace != -1 && neighbourHasOpacity({x,y,z})) {   // Dont draw blocks if not seen or if its air (-1)
                    blocks[world[x][y][z]]->draw({ x, y, z });
                }
            }
        }
    }

    glEndList();
}

void WorldManager::generateTree(const glm::ivec3 position) {

    // Draw leaves
    for (float polarAngle = 0; polarAngle < 3; polarAngle += 0.1) {     // Please dont use this method later
        for (float azimuthalAngle = 0; azimuthalAngle < 3; azimuthalAngle += 0.1) {
            double x = leafRadius * sin(polarAngle) * cos(azimuthalAngle);
            double y = leafRadius * sin(polarAngle) * sin(azimuthalAngle);
            double z = leafRadius * cos(polarAngle);
            glm::ivec3 offset = { x,y + treeHeight - leafRadius + 1,z };
            glm::ivec3 leafPos = position + offset;
            replaceBlock({ leafPos, 7 });
        }
    }
    // Draw chunk
    for (int i = 0; i < treeHeight; ++i) {
        replaceBlock({ {position.x, position.y + i, position.z}, 9});
    }
}

void WorldManager::generateBubble(const glm::ivec3 position) {      //Should put light in middle

    // Draw leaves
    for (float polarAngle = 0; polarAngle < 6.2; polarAngle += 0.1) {
        for (float azimuthalAngle = 0; azimuthalAngle < 6.2; azimuthalAngle += 0.1) { // Please dont use this method later
            double x = leafRadius * sin(polarAngle) * cos(azimuthalAngle);
            double y = leafRadius * sin(polarAngle) * sin(azimuthalAngle);
            double z = leafRadius * cos(polarAngle);
            glm::ivec3 offset = { x,y + treeHeight - leafRadius + 1,z };
            glm::ivec3 leafPos = position + offset;
            replaceBlock({ leafPos, 4 });
        }
    }
}

void WorldManager::explosion(const glm::ivec3 position) {

    for (float r = -2; r <= 4; r+=0.1) {
        for (float polarAngle = 0; polarAngle < 6.3; polarAngle += 0.1) {
            for (float azimuthalAngle = 0; azimuthalAngle < 6.3; azimuthalAngle += 0.1) { // Please dont use this method later
                int x = r * sin(polarAngle) * cos(azimuthalAngle);
                int y = r * sin(polarAngle) * sin(azimuthalAngle);
                int z = r * cos(polarAngle);
                world[x + position.x][y + position.y][z + position.z] = -1;      // Not a tree just copied from tree
            }
        }
    }
    glm::ivec2 chunkPos = { position.x / 16, position.z / 16 };

    chunksToUpdate.push_back({ chunkPos });//Also should update other chunks involved

}

void WorldManager::generateWorld() {

    PerlinNoise perlin;
    auto heightmap = perlin.generateHeightmap(worldLength, worldLength, 0.01, 0.01);

    for (int x = 0; x < worldLength; ++x) {
        for (int z = 0; z < worldLength; ++z) {
            auto heightOfColumn = std::floor( 70 * heightmap[x][z] + 200);
            for (int y = 0; y <= heightOfColumn; ++y) {

                if (y/heightOfColumn > 0.8) {
                    // Generate dirt between cobble and grass
                    world[x][y][z] = 8;
                }
                else {
                    // Generate cobblestone underground
                    world[x][y][z] = 11;
                }
                if (y == heightOfColumn) {      //Randomly generate trees if y>10

                    // Tree
                    std::uniform_int_distribution<int> distribution(0, 1000);// Random chance
                    if (y > 10 && distribution(gen) == 1) { 
                        treeHeight = heightOfColumn / 14;
                        leafRadius = heightOfColumn / 35;
                        generateTree({ x,y,z });
                    }

                    // Bubble
                    std::uniform_int_distribution<int> distribution2(0, 3000);// Random chance
                    if (distribution2(gen) == 1) {
                        // Create bubble
                        generateBubble({ x,y + 40,z });
                    }

                    // Generate grass block at top
                    world[x][y][z] = 6;
                }
                if (y == 0) {
                    // Generate bedrock at bottom
                    world[x][y][z] = 2;
                }
            }
        }
    }
}

void WorldManager::createProjectileAtLocation(const glm::vec3 position) {

    entities.push_back(new UnboundEntity());
    entities.back()->position = position;

}

bool WorldManager::posOutOfBounds(const glm::ivec3 pos) {

    if (pos.x >= 0 && pos.x < worldLength &&
        pos.y >= 0 && pos.y < worldHeight &&
        pos.z >= 0 && pos.z < worldLength) {
        return false;
    }
    return true;

}

void WorldManager::destroyBlock(const glm::ivec3 position) {

    if (!posOutOfBounds(position)) {
        world[position.x][position.y][position.z] = -1;
        chunksToUpdate.push_back({ position.x / 16,position.z / 16 });
    }
}

void WorldManager::moveProjectileToLocation(const glm::vec3 postion) {
    entities[0]->position = postion;
    entities[0]->velocity /= entities[0]->getSpeed();
}

int WorldManager::getBlockAtPos(const glm::ivec3 pos) {
    if (!posOutOfBounds(pos)) {
        return world[pos.x][pos.y][pos.z];
    }
    else {
        return -1;
    }
}

void WorldManager::updateAll() {

    entities[0]->applyForceTick({ 0, -0.05, 0 });
    entities[0]->updateTick();
    auto nextPos = entities[0]->getNextPosition();
    auto blockNoAtNext = getBlockAtPos(nextPos);
    if (blockNoAtNext != -1) {         // After checking this should cast another ray to see if colided with an object further back

        auto collisionPointAndNormal = blocks[blockNoAtNext]->getCollisionPointAndNormal(entities[0]->position, glm::normalize(entities[0]->velocity), glm::ivec3(nextPos));

        auto collisionPoint = collisionPointAndNormal.first;
        auto normal = collisionPointAndNormal.second;

        if (normal.x != 0 || normal.y != 0 || normal.z != 0) {
            entities[0]->handleCollision(normal, collisionPoint);
        }
    }

    // Copying above but for all entities
    for (const auto& entitiy : entities) {

        entitiy->applyForceTick({ 0, -0.05, 0 });
        entitiy->updateTick();
        auto nextPos = entitiy->getNextPosition();
        auto blockNoAtNext = getBlockAtPos(nextPos);
        if (blockNoAtNext != -1) {         // After checking this should cast another ray to see if colided with an object further back

            auto collisionPointAndNormal = blocks[blockNoAtNext]->getCollisionPointAndNormal(entitiy->position, glm::normalize(entitiy->velocity), glm::ivec3(nextPos));

            auto collisionPoint = collisionPointAndNormal.first;
            auto normal = collisionPointAndNormal.second;

            if (normal.x != 0 || normal.y != 0 || normal.z != 0) {
                entitiy->handleCollision(normal, collisionPoint);
            }
        }

    }
}