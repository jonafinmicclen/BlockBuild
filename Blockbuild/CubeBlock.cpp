#include "CubeBlock.h"

//Init
CubeBlock::CubeBlock(glm::vec3 startPosition) : RenderedObject() {
    position = startPosition;
    RenderedObject::loadTexture();

    // Front face (reversed order)
    addVertexAndTextureCoordinate({ {0.5f, -0.5f, -0.5f},   {1.0f, 0.0f} }); // 3
    addVertexAndTextureCoordinate({ {0.5f, 0.5f, -0.5f},    {1.0f, 1.0f} }); // 2
    addVertexAndTextureCoordinate({ {-0.5f, 0.5f, -0.5f},   {0.0f, 1.0f} }); // 1
    addVertexAndTextureCoordinate({ {-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f} }); // 0

    // Back face (reversed order)
    addVertexAndTextureCoordinate({ {0.5f, -0.5f, 0.5f},    {1.0f, 0.0f} }); // 7
    addVertexAndTextureCoordinate({ {0.5f, 0.5f, 0.5f},     {1.0f, 1.0f} }); // 6
    addVertexAndTextureCoordinate({ {-0.5f, 0.5f, 0.5f},    {0.0f, 1.0f} }); // 5
    addVertexAndTextureCoordinate({ {-0.5f, -0.5f, 0.5f},   {0.0f, 0.0f} }); // 4

    // Define the surfaces using vertex indices
    addSurface({ 0, 1, 2, 3 }); // Front face
    addSurface({ 4, 5, 6, 7 }); // Back face
    addSurface({ 0, 3, 7, 4 }); // Left face
    addSurface({ 1, 5, 6, 2 }); // Right face
    addSurface({ 1, 0, 4, 5 }); // Top face
    addSurface({ 3, 2, 6, 7 }); // Bottom face
}
