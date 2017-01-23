#pragma once
#include <glew\GL\glew.h>
#include <glfw\glfw3.h>
#include <string>
#include "../utils/Reader.h"

class GlProgram
{
public:

	GlProgram(const char * vertexshaderloc, const char* fragmentshaderloc);
	~GlProgram();
	void use()const;
	void unuse()const;
	inline GLuint& getProgramId() { return m_program_id; };

private:
	GLuint compile(const char * shaderloc, GLenum type);
	void link() const;

private:

	GLuint m_program_id, m_vs_id, m_fg_id;

};