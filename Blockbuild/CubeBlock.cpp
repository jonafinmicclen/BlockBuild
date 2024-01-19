#include "CubeBlock.h"

// Init
CubeBlock::CubeBlock() : RenderedObject() {

    const char* texturePath = "D:/JonsTests/terrain.png";    // Temp default texture
    RenderedObject::loadTexture(texturePath);

    // Texture coordinates
    glm::vec2 bottomLeft = { 0.0f, 0.0f };
    glm::vec2 topRight = { 1.0f, 1.0f };
    glm::vec2 topLeft = { 0.0f, 1.0f };
    glm::vec2 bottomRight = { 1.0f, 0.0f };

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
    addSurface({ 0, 1, 2, 3 }); // Front face
    addSurface({ 4, 5, 6, 7 }); // Back face
    addSurface({ 0, 3, 7, 4 }); // Left face
    addSurface({ 1, 5, 6, 2 }); // Right face
    addSurface({ 1, 0, 4, 5 }); // Top face
    addSurface({ 3, 2, 6, 7 }); // Bottom face
}
