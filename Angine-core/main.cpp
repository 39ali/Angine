#include<glew\GL\glew.h>
#include<iostream>
#include "src\graphics\Window.h"
#include "src\graphics\GlProgram.h"




int main()
{
	Window* win = new Window(800, 600, "yoo");
	GlProgram* program = new GlProgram("./shader/shader.vert", "./shader/shader.frag");
	std::cout << "opengl - " << glGetString(GL_VERSION) << " glsl verison :" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	GLfloat vert[] =
	{
		-0.5,0.5,0,
		-0.5,-0.5,0,
		0.5,-0.5,0,
		0.5,0.5,0
	};
	GLuint indecies[] =
	{
	0,1,2,
	2,0,3
	};
	GLuint vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!win->isClosed())
	{
		win->clear();

		program->use();

		glBindVertexArray(vao);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		program->unuse();
		win->update();
	}

	delete win;
	return 0;
}


