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
    GLuint displayList;
    RenderedObject();

    std::vector<glm::vec3> vertices = {};
    std::vector<std::pair<std::vector<int>, std::vector<glm::vec2>>> surfaces;

    glm::vec3 rotation_axis;

    float rotation_angle;
    glm::vec3 color;

    GLuint textureID;  // Texture ID for the loaded texture
    std::pair<float, float> texturePos;

    void addVertex(const glm::vec3& vertex);
    void addSurfaceAndTextureCoords(const std::pair< std::vector<int>, std::vector<glm::vec2> >& surface);
    void setColor(const glm::vec3& newColor);
    void loadTexture(const char* texturePath);
    void oldDraw(const glm::vec3 position);
    void draw(const glm::vec3 position);

    void drawWithDisplayList(const glm::vec3 position);

    void generateDisplayList();

};

#endif // RENDERED_OBJECT_H
