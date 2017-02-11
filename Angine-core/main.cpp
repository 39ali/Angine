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
	GlProgram* lampshader = new GlProgram("./shaders/lampshader.vert", "./shaders/lampshader.frag");
	GlProgram* modelshader = new GlProgram("./shaders/modelshader.vert", "./shaders/modelshader.frag");
	std::cout << "opengl - " << glGetString(GL_VERSION) << std::endl;




	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glm::vec3 lightPos(1.0f, 1.0f, 1.0f);

	FlyCamera flycam(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), win);



	GLuint vbo, lightvao;
	glGenVertexArrays(1, &lightvao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(lightvao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)0);
	glBindVertexArray(0);


	GLuint modelVao;
	glCreateVertexArrays(1, &modelVao);
	glBindVertexArray(modelVao);
	glBindVertexArray(modelVao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (const void*)(sizeof(GL_FLOAT) * 3));
	glBindVertexArray(0);




	glm::mat4   projection, mvp, view;

	glm::mat4 model;
	model = glm::translate(glm::vec3(0.0f, 0.0f, -2.0f));

	while (!win->isClosed())
	{
		win->clear();
		static double fisttime = Time::getTime();

		if (Time::getTime() - fisttime >= 1.0) {
			std::cout << "FPS: " << Time::getFps() << std::endl;
			fisttime = Time::getTime();
			std::cout << "DELTA : " << Time::getDeltaTime() << std::endl;
		}

		flycam.updatePosition();

		static float pov = 45;
		if (win->isKeyPressed(GLFW_KEY_Q))
		{
			pov -= 5 * (float)Time::getDeltaTime();
		}
		else if (win->isKeyPressed(GLFW_KEY_Z))
		{
			pov += (float)(5 * Time::getDeltaTime());
		}
		pov = glm::clamp(pov, 1.f, 90.f);
		projection = glm::perspective(glm::radians(pov), (float)((win->getWidth()) / win->getHeight()), 0.1f, 1000.f);



		view = flycam.getMatrix();



		lampshader->use();
		model = glm::translate(lightPos)*glm::scale(glm::vec3(0.2));
		mvp = projection*view * model;
		GLuint transformloc = glGetUniformLocation(lampshader->getProgramId(), "mvp");
		glUniformMatrix4fv(transformloc, 1, GL_FALSE, &mvp[0][0]);

		glBindVertexArray(lightvao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		lampshader->unuse();



		modelshader->use();
		model = glm::mat4();
		mvp = projection*view*model;
		glUniform3f(glGetUniformLocation(modelshader->getProgramId(), "cameraposition"), flycam.getposition().x, flycam.getposition().y, flycam.getposition().z);
		glUniform3f(glGetUniformLocation(modelshader->getProgramId(), "modelcolor"), 1.0f, 0.5f, 0.31f);
		glUniform3f(glGetUniformLocation(modelshader->getProgramId(), "lightcolor"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(modelshader->getProgramId(), "lightposition"), lightPos.x, lightPos.y, lightPos.z);
		glUniformMatrix4fv(glGetUniformLocation(modelshader->getProgramId(), "modelmatrix"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(modelshader->getProgramId(), "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
		glBindVertexArray(modelVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		modelshader->unuse();



		win->update();
	}

	delete win;
	return 0;
}


