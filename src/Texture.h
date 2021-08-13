#pragma once
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>


struct Texture {
	Texture(const std::string& filename, bool has_alpha_channel) {
        glGenTextures(1, &id);
        activate();
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, number_of_channels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &number_of_channels, 0);
        if (data)
        {
            auto format{ has_alpha_channel ? GL_RGBA : GL_RGB };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            throw std::exception("Failed to load texture");
        }
        stbi_image_free(data);
	}

    void set_to_texture_unit_and_activate(unsigned int i) {
        if (i > 15) {
            throw std::exception("Setting a texture to texture unit after #15 is not implemented.");
        }
        glActiveTexture(GL_TEXTURE0 + i);
        activate();
    }

    void activate() {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    unsigned int id;
};