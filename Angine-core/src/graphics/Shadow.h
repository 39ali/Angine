#pragma once
#include <glew\GL\glew.h>
class Shadow
{
public:
	Shadow();
	~Shadow();
	void bind();
	void unbind(unsigned int scrWidth, unsigned intscrHeight);
	GLuint getdepthTexture() { return m_depthMap; };
private:
	void init();
private:
	GLuint	m_fbo;
	GLuint m_depthMap;
	unsigned int  SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

};