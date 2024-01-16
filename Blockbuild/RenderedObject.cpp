#include "RenderedObject.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// init
RenderedObject::RenderedObject() {
    // Default color
    setColor({ 1, 1, 1 });
    textureID = 0;  // Initialize texture ID to 0
}

void RenderedObject::setColor(const glm::vec3& newColor) {
    color = newColor;
}

void RenderedObject::addVertexAndTextureCoordinate(const std::pair<glm::vec3, glm::vec2>& vertex) {
    vertices.push_back(vertex);
}

void RenderedObject::addSurface(const std::vector<int>& surfaceIndices) {
    surfaces.push_back(surfaceIndices);
}

void RenderedObject::loadTexture() {

    const char* texturePath = "C:/Users/Jonathan McClen/Documents/textures/cobblestone.png";    // Temp default texture
    int width, height, channels;
    unsigned char* image = stbi_load(texturePath, &width, &height, &channels, STBI_rgb);

    if (image) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set texture parameters (without mipmaps)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Set texture wrapping to clamp to edge
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);
    }
    else {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
}

void RenderedObject::draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation_angle, rotation_axis.x, rotation_axis.y, rotation_axis.z);

    if (textureID != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    glBegin(GL_QUADS);

    int surfaceCounter = 0;

    for (const auto& surface : surfaces) {
        for (const auto& vertexIndex : surface) {

            glm::vec3 vertex = vertices[vertexIndex].first;
            glm::vec2 textureCoord = vertices[vertexIndex].second;
            textureCoord += 10;

            if (textureID != 0) {
                glTexCoord2f(textureCoord.x, textureCoord.y);
            }

            //  glColor3fv(glm::value_ptr(color));
            glVertex3fv(glm::value_ptr(vertex));
        }
        surfaceCounter++;
    }

    glEnd();

    if (textureID != 0) {
        glDisable(GL_TEXTURE_2D);
    }

    glPopMatrix();
}
