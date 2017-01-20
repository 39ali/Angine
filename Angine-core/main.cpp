#include<glew\GL\glew.h>
#include<iostream>
#include "src\graphics\Window.h"
#include "src\graphics\GlProgram.h"




int main()
{
	Window* win = new Window(800, 600, "yoo");
	GlProgram* program = new GlProgram("./shader/shader.vert", "./shader/shader.frag");
	std::cout << "opengl - " << glGetString(GL_VERSION) << std::endl;


	GLfloat vert[]=
	{
		0,0.5f,0,
		0.5f,-.5,0,
		-0.5,-0.5,0
	};
	GLuint vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
	glBindVertexArray(0);

	while (!win->isClosed())
	{
		win->clear();

		program->use();

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
			program->unuse();
		win->update();
	}

	delete win;
	return 0;
}


