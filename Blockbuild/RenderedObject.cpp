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
    
void RenderedObject::draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation_angle, rotation_axis.x, rotation_axis.y, rotation_axis.z);

    // Enable texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);  // Assuming textureID is properly set before calling draw

    glBegin(GL_QUADS);

    for (const auto& surface : surfaces) {
        for (const auto& vertexIndex : surface) {

            glm::vec3 vertex = vertices[vertexIndex];

            // Set texture coordinates to cover the entire texture
            glTexCoord2f(0.0f, 0.0f);  // Bottom-left
            glVertex3fv(glm::value_ptr(vertex));

            glTexCoord2f(1.0f, 0.0f);  // Bottom-right
            glVertex3fv(glm::value_ptr(vertex));

            glTexCoord2f(1.0f, 1.0f);  // Top-right
            glVertex3fv(glm::value_ptr(vertex));

            glTexCoord2f(0.0f, 1.0f);  // Top-left
            glVertex3fv(glm::value_ptr(vertex));
        }
    }

    glEnd();

    // Disable texture
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

GLuint RenderedObject::loadTexture(const char* imagePath) {
    std::cout << imagePath;
    GLuint ID = SOIL_load_OGL_texture(
        imagePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
    );

    if (ID == 0) {
        printf("Texture loading failed: %s\n", SOIL_last_result());
    }

    // Corrected assignment
    textureID = ID;

    return ID;
}