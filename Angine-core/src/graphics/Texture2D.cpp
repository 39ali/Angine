#include "Texture2D.h"

Texture2D::Texture2D(const char * textureLocation,const   WrapType& wt ) : m_texture_id(0)
{
	if (textureLocation == "") { return; }
	int width, height;
	unsigned char* image = SOIL_load_image(textureLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	if (image == nullptr)
	{
		std::cout << "unable to load image" << ": " << textureLocation << std::endl;
	}
	glGenTextures(1, &m_texture_id);

	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	if (wt == CLAMP_TO_EDGE) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
Texture2D::~Texture2D()
{

}

void Texture2D::use(unsigned int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
}
void Texture2D::unuse()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}