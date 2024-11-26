#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GL/glew.h"

Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}

SharedPtr<Texture> Texture::Load(const char* fileName)
{
    int width, height, components;
    stbi_uc* imageData = stbi_load(fileName, &width, &height, &components, 4); // 4 = rgba channels 

    if (!imageData)
    {
        return nullptr;
    }

    uint32_t textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    // This specifies how textures are sampled when scaled up or down (min and mag filter)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // This is for wrapping, used when the texture coordinates are outside of 0-1 range
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    glGenerateMipmap(GL_TEXTURE_2D); // Generates mipmaps (lower resolution versions of the image for efficiency in rendering - used with LoDs)

    stbi_image_free(imageData); // Data is loaded to the GPU so we can free the memory now

    glm::ivec2 size = glm::ivec2(width, height);
    return std::make_shared<Texture>(textureId, size);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}

Texture::Texture(uint32_t textureId, glm::ivec2& size) :
    textureId(textureId),
    size(size)
{
}
