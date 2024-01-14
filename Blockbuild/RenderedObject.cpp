#include "RenderedObject.h"

//init
RenderedObject::RenderedObject() {
    //Default color
    setColor({ 1,1,1 });
}

void RenderedObject::setColor(const glm::vec3& newColor) {
    color = newColor;
}

void RenderedObject::addVertex(const glm::vec3& vertex) {
    vertices.push_back(vertex);
}

void RenderedObject::addSurface(const std::vector<int>& surfaceIndices) {
    surfaces.push_back(surfaceIndices);
}
    
void RenderedObject::draw() {   // This draw method is slow bc no VBO or list

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation_angle, rotation_axis.x, rotation_axis.y, rotation_axis.z);
    glBegin(GL_QUADS);

    for (const auto& surface : surfaces) {
        for (const auto& vertexIndex : surface) {

            glm::vec3 vertex = vertices[vertexIndex];
            glColor3f(color.x, color.y, color.z);
            glVertex3fv(glm::value_ptr(vertex));

        }
    }

    glEnd();
    glPopMatrix();
}