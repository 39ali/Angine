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

	GlProgram lightingShader("./shaders/basic_lighting.vs", "./shaders/basic_lighting.frag");
	//GlProgram lampShader("./shaders/lamp.vs", "./shaders/lamp.frag");
	Model ourModel("./models/nanosuit/nanosuit.obj");

	FlyCamera camera(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), win);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

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

		glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), "viewPos"), camera.getposition().x, camera.getposition().y, camera.getposition().z);


		for (std::size_t i = 0; i < 4; i++)
		{
			std::string s = "pointLights[" + std::to_string(i) + "]";
			glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), (s + ".position").c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
			glUniform1f(glGetUniformLocation(lightingShader.getProgramId(), (s + ".constant").c_str()), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.getProgramId(), (s + ".linear").c_str()), 0.09);
			glUniform1f(glGetUniformLocation(lightingShader.getProgramId(), (s + ".quadratic").c_str()), 0.032);
			glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), (s + ".ambient").c_str()), 0.2f, 0.2f, 0.2f);
			glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), (s + ".diffuse").c_str()), 0.5f, 0.5f, 0.5f);
			glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), (s + ".specular").c_str()), 1.0f, 1.0f, 1.0f);
		}
		glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), "dirLight.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), "dirLight.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), "dirLight.specular"), 1.0f, 1.0f, 1.0f);

		GLuint idd = glGetUniformLocation(lightingShader.getProgramId(), "material.shininess");
		glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), "lightColor"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.getProgramId(), "dirLight.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform1f(idd, 32.0f);

		ourModel.Draw(&lightingShader);


		lightingShader.unuse();


		win->update();
	}

	delete win;
	return 0;
}


