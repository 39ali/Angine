#include<glew\GL\glew.h>
#include<iostream>
#include "src\graphics\Window.h"
#include "src\graphics\GlProgram.h"
#include "src\graphics\Texture2D.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "src\Cameras\FlyCamera.h"
#include "src\graphics\model.h"

int main()
{
	Window* win = new Window(800, 600, "yoo");

	std::cout << "opengl - " << glGetString(GL_VERSION) << std::endl;
	glfwSwapInterval(1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GlProgram lightingShader("./shaders/basic.vs", "./shaders/basic.frag");
	GlProgram lampShader("./shaders/lamp.vs", "./shaders/lamp.frag");
	Model ourModel("./models/nanosuit/nanosuit.obj");

	FlyCamera camera(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), win);


	glm::vec3 lightPosition(1.2, 1, 2);

	while (!win->isClosed())
	{

		win->clear();
		static double fisttime = Time::getTime();
		if (Time::getTime() - fisttime >= 2.0) {
			std::cout << "FPS: " << Time::getFps() << std::endl;
			fisttime = Time::getTime();
		}

		camera.updatePosition();
		lightingShader.use();

		glm::mat4  view, projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)win->getWidth() / (float)win->getHeight(), 0.1f, 100.0f);
		view = camera.getMatrix();
		GLuint projectionLoc = glGetUniformLocation(lightingShader.getProgramId(), "projection");
		GLuint viewLoc = glGetUniformLocation(lightingShader.getProgramId(), "view");

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.getProgramId(), "model"), 1, GL_FALSE, glm::value_ptr(model));


		ourModel.Draw(&lightingShader);


		lightingShader.unuse();


		win->update();
	}

	delete win;
	return 0;
}


