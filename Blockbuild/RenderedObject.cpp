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

void RenderedObject::addVertex(const glm::vec3& vertex) {
    vertices.push_back(vertex);
}

void RenderedObject::addSurfaceAndTextureCoords(const std::pair< std::vector<int>, std::vector<glm::vec2> >& surface) {
    surfaces.push_back(surface);
}

void RenderedObject::loadTexture(const char* texturePath) {

    int width, height, channels;
    unsigned char* image = stbi_load(texturePath, &width, &height, &channels, STBI_rgb_alpha);

    if (image) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Set texture parameters (without mipmaps)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Set texture wrapping to clamp to edge
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Upload image data to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);
    }
    else {
        std::cout << "[RenderedObject]:Failed to load texture\n";
    }
}

void RenderedObject::oldDraw(const glm::vec3 position) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation_angle, rotation_axis.x, rotation_axis.y, rotation_axis.z);

    if (textureID != 0) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    glBegin(GL_QUADS);

    for (const auto& surface : surfaces) {

        int vertexCounter = 0;

        for (const auto& vertexIndex : surface.first) {

            glm::vec2 textureCoord = surface.second[vertexCounter];    //Use new set for uv coords for each face
            glm::vec3 vertex = vertices[vertexIndex];
            vertexCounter++;

            if (textureID != 0) {
                glTexCoord2f(textureCoord.x, textureCoord.y);
            }
            glVertex3fv(glm::value_ptr(vertex));

        }
    }

    glEnd();

    if (textureID != 0) {
        glDisable(GL_TEXTURE_2D);
    }

    glPopMatrix();
}

void RenderedObject::draw(const glm::vec3 position) {


    oldDraw(position);
    //drawWithDisplayList(position);

}

void RenderedObject::drawWithDisplayList(const glm::vec3 position) {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation_angle, rotation_axis.x, rotation_axis.y, rotation_axis.z);
    // Use display list
    glCallList(displayList);
    glPopMatrix();
}

void RenderedObject::generateDisplayList() {

    glDeleteLists(displayList, 1);

    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);

    // Draw
    draw({0,0,0});

    glEndList();

}