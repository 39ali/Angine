#pragma once
#include <glm\glm.hpp>
#include "GlProgram.h"
#include "Texture2D.h"
#include <glew\GL\glew.h>
#include <cstddef>
struct  VertexeData
{

	glm::vec2 pos;
	glm::vec2 uv;
	VertexeData(glm::vec2& _pos, glm::vec2& _uv)
	{
		pos = _pos;
		_uv = _uv;
	}

};

class SpriteRenderer
{
public:
	SpriteRenderer(GlProgram* shader);
	~SpriteRenderer();
	void draw(const glm::vec2& pos, const glm::vec2& size,
		const glm::float32 rot, Texture2D& tex, const glm::vec3 color = glm::vec3(1.0f));
private:
	void initRenderData();
	void init();
private:
	GlProgram* m_shader;
	GLuint m_vbo, m_ibo, m_vao;
};