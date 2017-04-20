#include "SpriteRenderer.h"
#include <glm\gtc\matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(GlProgram* shader) :m_shader(shader)
{
	init();
	//initRenderData();
}
SpriteRenderer::~SpriteRenderer()
{
	delete m_shader;
}

void SpriteRenderer::init()
{
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
	};

	VertexeData varr[] = {
		VertexeData(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f))
		,VertexeData(glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 1.0f))
		,VertexeData(glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 1.0f))
		,VertexeData(glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 0.0f))
	};
	GLushort indicies[] = { 0, 1, 2 , 2,3, 0 };

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(varr), varr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	int iii = offsetof(VertexeData, uv);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexeData), (GLvoid*)(offsetof(VertexeData, pos)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexeData), (GLvoid*)(offsetof(VertexeData,pos)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	glBindVertexArray(0);

}

////void SpriteRenderer::initRenderData()
//{
//	// Configure VAO/VBO
//	GLuint VBO;
//	GLfloat vertices[] = {
//		// Pos      // Tex
//		0.0f, 0.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f,
//
//		0.0f, 0.0f, 0.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 0.0f, 1.0f, 0.0f
//	};
//
//	glGenVertexArrays(1, &m_vao);
//	glGenBuffers(1, &VBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindVertexArray(m_vao);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}

void SpriteRenderer::draw( const glm::vec2& pos, const glm::vec2& size,
	const glm::float32 rot,  Texture2D& tex ,const glm::vec3 color)
{
	m_shader->use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(pos, 0));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	tex.use(0);
	m_shader->setUniform("img", 0);
	m_shader->setUniform("model", model);
	m_shader->setUniform("objcolor", color);
	glBindVertexArray(m_vao);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);
	m_shader->unuse();
}
