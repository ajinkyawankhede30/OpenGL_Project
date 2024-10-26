
#include "Textures.h"
#include "stb_image/stb_image.h"
#include "GL/glew.h"
#include "glfw3.h"

Textures::Textures(const std::string& filename)
	:m_rendererID(0), m_imgBuffer(nullptr),
	 m_width(0), m_height(0), m_BPP(0),
	 m_imgPath(filename)
{
	stbi_set_flip_vertically_on_load(1);
	m_imgBuffer = stbi_load(filename.c_str(), &m_width, &m_height, &m_BPP, 0);

	glGenTextures(1, &m_rendererID);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (m_imgBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB ,GL_UNSIGNED_BYTE, (const void*)m_imgBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture.\n";	
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_imgBuffer)
		stbi_image_free(m_imgBuffer);
}

void Textures::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void Textures::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Textures::~Textures()
{
	glDeleteTextures(1, &m_rendererID);
}