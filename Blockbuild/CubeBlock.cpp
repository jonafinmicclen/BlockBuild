#include "CubeBlock.h"

// Init
CubeBlock::CubeBlock() : RenderedObject::RenderedObject()  {

    const char* texturePath = "D:/JonsTests/realTerrain.png";    // Temp default texture
    RenderedObject::loadTexture(texturePath);

    texturePos.first = 1;
    texturePos.second = 2;
    // Texture coordinates
    glm::vec2 bottomLeft = { 0.0f / 16 + texturePos.first / 16, 0.0f / 16 + texturePos.second / 16 };
    glm::vec2 topRight = { 1.0f / 16 + texturePos.first / 16, 1.0f / 16 + texturePos.second / 16 };
    glm::vec2 topLeft = { 0.0f / 16 + texturePos.first / 16, 1.0f / 16 + texturePos.second / 16 };
    glm::vec2 bottomRight = { 1.0f / 16 + texturePos.first / 16, 0.0f / 16 + texturePos.second / 16 };
    std::vector<glm::vec2> allCornersCoords = { topLeft , topRight, bottomRight, bottomLeft };

    // Front face
    addVertexAndTextureCoordinate({ {-0.5f, -0.5f, -0.5f}, bottomLeft });       // Bottom left
    addVertexAndTextureCoordinate({ {0.5f, -0.5f, -0.5f}, bottomRight });      // Bottom right
    addVertexAndTextureCoordinate({ {0.5f, 0.5f, -0.5f}, topRight });          // Top right
    addVertexAndTextureCoordinate({ {-0.5f, 0.5f, -0.5f}, topLeft });          // Top left

    // Back face
    addVertexAndTextureCoordinate({ {-0.5f, -0.5f, 0.5f}, bottomLeft });       // Bottom left
    addVertexAndTextureCoordinate({ {0.5f, -0.5f, 0.5f}, bottomRight });      // Bottom right
    addVertexAndTextureCoordinate({ {0.5f, 0.5f, 0.5f}, topRight });          // Top right
    addVertexAndTextureCoordinate({ {-0.5f, 0.5f, 0.5f}, topLeft });          // Top left

    // Define the surfaces using vertex indices
    addSurface({ { 0, 1, 2, 3 }, allCornersCoords }); // Front face
    addSurface({ { 4, 5, 6, 7 }, allCornersCoords }); // Back face
    addSurface({ { 0, 3, 7, 4 }, allCornersCoords }); // Left face
    addSurface({ { 1, 5, 6, 2 }, allCornersCoords }); // Right face
    addSurface({ { 1, 0, 4, 5 }, allCornersCoords }); // Top face
    addSurface({ { 3, 2, 6, 7 }, allCornersCoords }); // Bottom face
}
