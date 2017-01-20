#pragma once
#define GLFW_STATIC
#include <glew\GL\glew.h>
class  SimpleRenderer
{
public:
	SimpleRenderer();
	~SimpleRenderer();
	void render();
private:
	GLuint m_vbo, m_vao;

};