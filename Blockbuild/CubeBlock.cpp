#include "CubeBlock.h"

void CubeBlock::setTexturePos(const std::pair<float, float> position) {
    CubeBlock::texturePos = position;
}

void CubeBlock::setVertexAndCoords() {

    const char* texturePath = "D:/JonsTests/realTerrain.png";    // Temp default texture
    RenderedObject::loadTexture(texturePath);

    // Texture coordinates
    glm::vec2 bottomLeft = { 0.0f / 16 + texturePos.first / 16, 0.0f / 16 + texturePos.second / 16 };
    glm::vec2 topRight = { 1.0f / 16 + texturePos.first / 16, 1.0f / 16 + texturePos.second / 16 };
    glm::vec2 topLeft = { 0.0f / 16 + texturePos.first / 16, 1.0f / 16 + texturePos.second / 16 };
    glm::vec2 bottomRight = { 1.0f / 16 + texturePos.first / 16, 0.0f / 16 + texturePos.second / 16 };
    std::vector<glm::vec2> allCornersCoords = { topLeft , topRight, bottomRight, bottomLeft };

    // Front face
    addVertex({ -0.5f, -0.5f, -0.5f });       // Bottom left
    addVertex({ 0.5f, -0.5f, -0.5f });      // Bottom right
    addVertex({ 0.5f, 0.5f, -0.5f });          // Top right
    addVertex({ -0.5f, 0.5f, -0.5f });          // Top left

    // Back face
    addVertex({ -0.5f, -0.5f, 0.5f });       // Bottom left
    addVertex({ 0.5f, -0.5f, 0.5f });      // Bottom right
    addVertex({ 0.5f, 0.5f, 0.5f });          // Top right
    addVertex({ -0.5f, 0.5f, 0.5f });          // Top left

    // Define the surfaces using vertex indices
    addSurfaceAndTextureCoords({ { 0, 1, 2, 3 }, allCornersCoords }); // Front face
    addSurfaceAndTextureCoords({ { 4, 5, 6, 7 }, allCornersCoords }); // Back face
    addSurfaceAndTextureCoords({ { 0, 3, 7, 4 }, allCornersCoords }); // Left face
    addSurfaceAndTextureCoords({ { 1, 5, 6, 2 }, allCornersCoords }); // Right face
    addSurfaceAndTextureCoords({ { 1, 0, 4, 5 }, allCornersCoords }); // Top face
    addSurfaceAndTextureCoords({ { 3, 2, 6, 7 }, allCornersCoords }); // Bottom face
}

// Init
CubeBlock::CubeBlock() : RenderedObject::RenderedObject()  {

    setVertexAndCoords();
}