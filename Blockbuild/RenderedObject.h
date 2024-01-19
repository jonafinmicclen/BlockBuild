#ifndef RENDERED_OBJECT_H
#define RENDERED_OBJECT_H

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <glm/glm.hpp>
#include <float.h>
#include <glm/gtc/type_ptr.hpp> 


class RenderedObject {
public:

    RenderedObject();

    std::vector<std::pair<glm::vec3, glm::vec2>> vertices = {};
    std::vector<std::vector<int>> surfaces = {};

    glm::vec3 rotation_axis;

    float rotation_angle;
    glm::vec3 color;

    GLuint textureID;  // Texture ID for the loaded texture

    void addVertexAndTextureCoordinate(const std::pair<glm::vec3, glm::vec2>& vertex);
    void addSurface(const std::vector<int>& surfaceIndices);
    void setColor(const glm::vec3& newColor);
    void loadTexture(const char* texturePath);
    void draw(const glm::vec3 position);
};

#endif // RENDERED_OBJECT_H
