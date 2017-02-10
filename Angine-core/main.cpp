#include<glew\GL\glew.h>
#include<iostream>
#include "src\graphics\Window.h"
#include "src\graphics\GlProgram.h"
#include "src\graphics\Texture2D.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "src\Cameras\FlyCamera.h"




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



	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	FlyCamera flycam(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), win);



	GLuint vbo, vao;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0);

	/*glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (const void *)(sizeof(GLfloat) * 3));
*/
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (const void *)(sizeof(GLfloat) * 3));
	glBindVertexArray(0);



	glm::mat4   projection, mvp;

	//projection = glm::ortho(-800.f, 800.f, -600.f, 600.f,-2.f,100.f);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	while (!win->isClosed())
	{
		win->clear();

		program->use();
		glBindVertexArray(vao);

		for (size_t i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++) {

			glm::mat4 model;
			model *= glm::translate(cubePositions[i]);

			if (i % 2 != 0) {
				model *= glm::rotate((float)glfwGetTime()* glm::radians(55.0f)*i, glm::vec3(0.5, 0.3, 0));
			}

			GLfloat radius = 10.0f;
			GLfloat camx = sin(glfwGetTime())*radius;
			GLfloat camz = cos(glfwGetTime())*radius;

			flycam.updatePosition();

			static float pov = 45;
			if (win->isKeyPressed(GLFW_KEY_Q))
			{
				pov -= 0.005;
			}
			else if (win->isKeyPressed(GLFW_KEY_Z))
			{ 
				pov += 0.005;
				
			}
			pov = glm::clamp(pov, 1.f, 90.f);
			projection = glm::perspective(glm::radians(pov), (float)((win->getWidth()) / win->getHeight()), 0.1f, 1000.f);


			glm::mat4  view;
			view = flycam.getMatrix(); // glm::lookAt(glm::vec3(camx, 0, camz), glm::vec3(0, 0, 0), glm::vec3(0, 1.0, 0.0));
			mvp = projection*view * model;


			GLuint transformloc = glGetUniformLocation(program->getProgramId(), "mvp");
			glUniformMatrix4fv(transformloc, 1, GL_FALSE, &mvp[0][0]);


			texture0->use(0);
			glUniform1i(glGetUniformLocation(program->getProgramId(), "tex0"), 0);



			texture1->use(1);
			glUniform1i(glGetUniformLocation(program->getProgramId(), "tex1"), 1);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		program->unuse();
		win->update();
	}

	delete win;
	return 0;
}


