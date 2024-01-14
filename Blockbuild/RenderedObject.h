#ifndef RENDERED_OBJECT_H
#define RENDERED_OBJECT_H

#include <GL/glut.h>
#include <vector>
#include <glm/glm.hpp>
#include <float.h>
#include <glm/gtc/type_ptr.hpp> 

class RenderedObject {
public:

    RenderedObject();

    std::vector<glm::vec3> vertices = {};
    std::vector<std::vector<int>> surfaces = {};

    glm::vec3 position;
    glm::vec3 rotation_axis;

    float rotation_angle;
    glm::vec3 color;

    void addVertex(const glm::vec3& vertex);
    void addSurface(const std::vector<int>& surfaceIndices);
    void setColor(const glm::vec3& newColor);
    void draw();
};

#endif // RENDERED_OBJECT_H
