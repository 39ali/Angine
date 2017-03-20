#include "FrameBuffer.h"
#include <iostream>
FrameBuffer::FrameBuffer(int width, int height, bool depth, bool stencil) :m_width(width), m_height(height), m_vao(0)
{
	init(depth, stencil);
};
FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_FrameBufferID);
	glDeleteTextures(1, &m_textureID);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void FrameBuffer::init(bool depth, bool stencil)
{
	glGenFramebuffers(1, &m_FrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
	generateTexture(depth, stencil);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);

	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	initQuadBuffer();
}

void FrameBuffer::generateTexture(bool depth, bool stencil)
{
	GLenum attachment;
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	if (!depth && !stencil)
	{
		attachment = GL_RGB;
	}
	else if (depth && !stencil)
	{
		attachment = GL_DEPTH_COMPONENT;
	}
	else if (!depth && stencil) {
		attachment = GL_STENCIL_INDEX;
	}

	if (attachment == GL_RGB)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, attachment, m_width, m_height, 0, attachment, GL_UNSIGNED_BYTE, NULL);
	}
	else { glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL); }

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(0, m_textureID);

}

void FrameBuffer::initQuadBuffer() const {
	GLfloat quadVertices[] = {
		// Positions   // TexCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};
	glGenVertexArrays(1, &(GLuint)m_vao);
	glGenBuffers(1, &(GLuint)m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (const void *)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (const void *)(sizeof(GLfloat) * 2));
	glBindVertexArray(0);
};

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}
void FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::draw(GlProgram* shader)const
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	shader->use();
	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glActiveTexture(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	shader->unuse();
}


