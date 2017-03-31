#pragma once
#include <string>
#include <glm\glm.hpp>
#include "GlProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>


struct Character {
	GLuint     TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint     Advance;
};



class Label
{
public:
	Label();
	~Label();
	void drawString(const std::string& text, const glm::vec2& position, float scale, const glm::vec3& color) const;
private:
	void init();
	void loadChars();
	void initBuffer();
private:
	GlProgram * m_shader;
	FT_Library m_ft;
	FT_Face m_face;
	std::map<char, Character> m_Characters;
	GLuint m_vao, m_vbo;
};