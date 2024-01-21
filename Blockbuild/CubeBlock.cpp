#include "CubeBlock.h"

void CubeBlock::setTexturePos(const std::pair<float, float> position) {
    CubeBlock::texturePos = position;
}

void CubeBlock::setAllFacesUV(std::vector<glm::vec2> allCoords) {  // Takes coordiates of all corners and creates each face with it

    for (const auto& face : defaultFaceOrder) {
        setAFaceUV({ face, {allCoords} });
    }
}

void CubeBlock::rotateFaceACW(int surfaceIndex) {

    auto& oldSurface = surfaces[surfaceIndex].first;
    std::vector<int> newSurface;
    for (int i = 1; i < oldSurface.size(); i++) {
        newSurface.push_back(oldSurface[i]);
    }
    newSurface.push_back(oldSurface[0]);
    surfaces[surfaceIndex].first = newSurface;
}

void CubeBlock::rotateFaceCW(int surfaceIndex) {

    auto& oldSurface = surfaces[surfaceIndex].first;
    std::vector<int> newSurface;
    newSurface.push_back(oldSurface.back());
    for (int i = 0; i < oldSurface.size()-1; i++) {
        newSurface.push_back(oldSurface[i]);
    }
    surfaces[surfaceIndex].first = newSurface;
}

void CubeBlock::setAFaceUV(const std::pair<char, std::vector < glm::vec2>> faceAndCoords) {
    switch (faceAndCoords.first) {
    case'F':
        addSurfaceAndTextureCoords({ { 0, 1, 2, 3 }, faceAndCoords.second }); // Front face
        break;
    case'B':
        addSurfaceAndTextureCoords({ { 4, 5, 6, 7 }, faceAndCoords.second }); // Back face
        break;
    case'L':
        addSurfaceAndTextureCoords({ { 0, 3, 7, 4 }, faceAndCoords.second }); // Left face
        break;
    case'R':
        addSurfaceAndTextureCoords({ { 1, 5, 6, 2 }, faceAndCoords.second }); // Right face
        break;
    case'T':
        addSurfaceAndTextureCoords({ { 1, 0, 4, 5 }, faceAndCoords.second }); // Top face
        break;
    case'D':
        addSurfaceAndTextureCoords({ { 3, 2, 6, 7 }, faceAndCoords.second }); // Down face
        break;
    }
}

void CubeBlock::setAllCornersFromTopLeft(const glm::vec2 corner) {

    bottomLeft = { 0.0f / 16 + corner.x / 16, 0.0f / 16 + corner.y / 16 };
    topRight = { 1.0f / 16 + corner.x / 16, 1.0f / 16 + corner.y / 16 };
    topLeft = { 0.0f / 16 + corner.x / 16, 1.0f / 16 + corner.y / 16 };
    bottomRight = { 1.0f / 16 + corner.x / 16, 0.0f / 16 + corner.y / 16 };
    allCornersCoords = { topLeft , topRight, bottomRight, bottomLeft };

}

void CubeBlock::setVertexAndCoords() {      //This is dodgy, works tho
    
    // Texture coordinates
    setAllCornersFromTopLeft({ texturePos.first, texturePos.second });

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

}

// Init
CubeBlock::CubeBlock() : RenderedObject::RenderedObject()  {

    const char* texturePath = "../BlockBuild/textures.png";    // Temp default texture
    RenderedObject::loadTexture(texturePath);

    setVertexAndCoords();
}