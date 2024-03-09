#include <tngin/rendering/texture.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace TAL {
    Texture::Texture(GLenum TextureTarget, const std::string& FileName)
    {
        _textureTarget = TextureTarget;
        _fileName      = FileName;
    }

    bool Texture::Load()
    {
        stbi_set_flip_vertically_on_load(true);
        int width = 0, height = 0, bpp = 0;
        unsigned char* image_data = stbi_load(_fileName.c_str(), &width, &height, &bpp, 0);

        if (!image_data) {
            printf("Error loading texture: %s\n", _fileName.c_str());
            exit(0);
        }

        printf("Width %d, Height %d, BPP %d\n", width, height, bpp);

        glGenTextures(1, &_textureObj);
        glBindTexture(_textureTarget, _textureObj);
        if (_textureTarget == GL_TEXTURE_2D) {
            glTexImage2D(_textureTarget, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
        }
        else {
            printf("Texture target not supported\n");
        }

        glTexParameterf(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glBindTexture(_textureTarget, 0);

        return true;
    }

    void Texture::Bind(GLenum TextureUnit)
    {
        glActiveTexture(TextureUnit);
        glBindTexture(_textureTarget, _textureObj);
    }
}