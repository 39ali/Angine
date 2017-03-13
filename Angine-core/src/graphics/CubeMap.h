#pragma once
#include<glew\GL\glew.h>
#include <vector>
#include <soil\src\SOIL.h>
#include <glm\glm.hpp>
#include "GlProgram.h"
class CubeMap
{
public:
	CubeMap(const std::vector<const char*>& Cubemaps);
	~CubeMap();
	void draw(const glm::mat4& projection, const glm::mat4& view) const;

private:
	void loadCubeMap(const std::vector<const char*>& Cubemaps);
	void loadVert();

private:
	GLuint m_textureID;
	GLuint m_Vao;
	GlProgram * m_shader;
};