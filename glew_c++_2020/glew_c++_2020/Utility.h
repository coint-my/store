#pragma once
#ifndef UTILITY_H
#define UTILITY_H

#include "include/GL/glew.h"

#include "src/SOIL.h"
#pragma comment(lib, "src/SOIL.lib")

namespace my
{
	/*static GLuint* texture;
	static int count = 0;*/

	class myTexture
	{
	private:
		unsigned char* image;
	public:
		GLuint texture;

		myTexture(const char* _pathTexture)
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

			// Load image, create texture and generate mipmaps
			int width, height;
			unsigned char* image = SOIL_load_image(_pathTexture, &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
		}

		~myTexture()
		{
			image = 0;
		}
	};
}

#endif