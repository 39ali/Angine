#pragma once
#include <glew\GL\glew.h>
#include "GlProgram.h"
class FrameBuffer
{

public:
	FrameBuffer(int width, int height, bool depth = false, bool stencil = false);
	~FrameBuffer();
	void bind() const;
	void unbind();
	void draw(GlProgram* shader)const;
private:
	void init(bool depth, bool stencil);
	void generateTexture(bool depth, bool stencil);
	void initQuadBuffer() const;
private:
	GLuint m_textureID;
	GLuint m_FrameBufferID;
	int m_width, m_height;
	GLuint m_vao;
	GLuint  m_vbo;
};