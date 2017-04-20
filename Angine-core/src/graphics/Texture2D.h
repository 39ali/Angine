#pragma once
#include <glew\GL\glew.h>
#include <soil\src\SOIL.h>
#include <iostream>

enum WrapType 
{
REPEAT ,CLAMP_TO_EDGE 
};

class Texture2D
{
public:
	Texture2D(const char * textureLocation, const WrapType& wt = CLAMP_TO_EDGE);
	~Texture2D();
	void use(unsigned int textureUnit);
	void unuse();
	GLuint getID() const { return m_texture_id; };

private:
	GLuint m_texture_id;


};