#pragma once
#include <string>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <freetype-gl\freetype-gl.h>
#include "GlProgram.h"
#include <vector>

#define MAX_BUFFER_SIZE sizeof(vertexData)*4*10000
struct vertexData
{
	glm::vec3 position;
	glm::vec2 uv;
};

class Text
{
public:
	Text(const std::string& text, const glm::vec3& pos, const glm::vec3& color);
	~Text();
	void draw();
	void drawsprite();
private:
	std::string m_text;
	glm::vec3 m_pos;
	glm::vec3 m_color;
	ftgl::texture_atlas_t * m_texture_atlas;
	ftgl::texture_font_t * m_font;
	GLuint m_vao, m_vbo, m_ibo;
	GlProgram * m_shader;
};