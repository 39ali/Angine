#include "Text.h"
#include <stddef.h>  
Text::Text(const std::string& text, const glm::vec3& pos, const glm::vec3& color) :
	m_text(text), m_pos(pos), m_color(color)//, m_texture_atlas(NULL), m_font(NULL)
{
	using namespace ftgl;
	m_texture_atlas = texture_atlas_new(512, 512, 1);
	m_font = texture_font_new_from_file(m_texture_atlas, 200, "./fonts/arial.ttf");
	texture_font_get_glyph(m_font, 'A');
	//texture_font_delete(m_font);

	m_shader = new GlProgram("./shaders/textShader.vs", "./shaders/textShader.frag");

	glGenTextures(1, &m_texture_atlas->id);
	glBindTexture(GL_TEXTURE_2D, m_texture_atlas->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_texture_atlas->width, m_texture_atlas->height,
		0, GL_RED, GL_UNSIGNED_BYTE, m_texture_atlas->data);

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
	m_shader->use();
	m_shader->setUniform("mvp", projection);
	glUniform1i(glGetUniformLocation(m_shader->getProgramId(), "texid"), 0);
	m_shader->unuse();

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (const void *)offsetof(vertexData, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (const void *)offsetof(vertexData, uv));
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	unsigned int indices[] = { 0,1,2,2,0,3 };

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

}
Text::~Text()
{


}


void  Text::drawsprite()
{
	std::vector<vertexData> v;

	vertexData v1, v2, v3, v4;

	v1.position = glm::vec3(10, 10, 0);
	//	v1.uv
	v2.position = glm::vec3(10, 20, 0);
	v3.position = glm::vec3(20, 20, 0);
	v4.position = glm::vec3(20, 10, 0);

	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);

	m_shader->use();

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, v.size()*sizeof(vertexData), &v[0]);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

	m_shader->unuse();
}

void Text::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture_atlas->id);
	glActiveTexture(GL_TEXTURE0);
	float x = m_pos.x;
	float y = m_pos.y;
	std::vector<vertexData> v;
	for (int i = 0; i < 2; i++) {
		const char  cc = m_text.at(i);
		ftgl::texture_glyph_t *glyph = texture_font_get_glyph(m_font, cc);
		if (glyph != NULL) {
			float x0 = (x + glyph->offset_x);
			float y0 = (y + glyph->offset_y);
			float x1 = (x0 + glyph->width);
			float y1 = (y0 - glyph->height);

			float s0 = glyph->s0;
			float t0 = glyph->t0;
			float s1 = glyph->s1;
			float t1 = glyph->t1;


			vertexData v1, v2, v3, v4;

			v1.position = glm::vec3(x0, y0, 0);
			v1.uv = glm::vec2(s0, t0);

			v2.position = glm::vec3(x0, y1, 0);
			v2.uv = glm::vec2(s0, t1);

			v3.position = glm::vec3(x1, y1, 0);
			v3.uv = glm::vec2(s1, t1);

			v4.position = glm::vec3(x1, y0, 0);
			v4.uv = glm::vec2(s1, t0);

			v.push_back(v1);
			v.push_back(v2);
			v.push_back(v3);
			v.push_back(v4);
			x += glyph->advance_x;
		}
	}
	m_shader->use();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, m_texture_atlas->id);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, v.size()*sizeof(vertexData), &v[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	float count = (v.size() / 4) * 6;
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)0);
	glDisable(GL_BLEND);
	m_shader->unuse();


}