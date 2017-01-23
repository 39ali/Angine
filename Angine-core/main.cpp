#include<glew\GL\glew.h>
#include<iostream>
#include "src\graphics\Window.h"
#include "src\graphics\GlProgram.h"
#include "src\graphics\Texture2D.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>




int main()
{
	Window* win = new Window(800, 600, "yoo");
	GlProgram* program = new GlProgram("./shaders/shader.vert", "./shaders/shader.frag");
	std::cout << "opengl - " << glGetString(GL_VERSION) << std::endl;

	Texture2D * texture0 = new Texture2D("./textures/wall.jpg");
	Texture2D * texture1 = new Texture2D("./textures/container.jpg");

	GLfloat vert[] =
	{
		0,0.5f,0,    1,0,0,  0.5,1,
		0.5f,-.5,0,  0,1,0,  1,0,
		-0.5,-0.5,0 ,0,0,1   ,0,0
	};
	GLuint vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (const void *)(sizeof(GLfloat) * 3));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (const void *)(sizeof(GLfloat) * 6));
	glBindVertexArray(0);



	glm::mat4 trans;

	trans *= glm::translate(glm::vec3(-0.3, 0, 0));





	while (!win->isClosed())
	{
		win->clear();

		program->use();

		trans *= glm::rotate(glm::radians(2.2f), glm::vec3(1,0, 0.0));
		GLuint transformloc = glGetUniformLocation(program->getProgramId(), "mvp");
		glUniformMatrix4fv(transformloc, 1, GL_FALSE, &trans[0][0]);

		glBindVertexArray(vao);

		texture0->use(0);
		glUniform1i(glGetUniformLocation(program->getProgramId(), "tex0"), 0);


		texture1->use(1);
		glUniform1i(glGetUniformLocation(program->getProgramId(), "tex1"), 1);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		program->unuse();
		win->update();
	}

	delete win;
	return 0;
}


