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
#include "src\graphics\lights\DirectionLight.h"
#include "src\graphics\lights\PointLight.h"
#include "src\graphics\CubeMap.h"
#include "src\graphics\FrameBuffer.h"
#include <vector>


GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
	GLenum attachment_type;
	if (!depth && !stencil)
		attachment_type = GL_RGB;
	else if (depth && !stencil)
		attachment_type = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachment_type = GL_STENCIL_INDEX;

	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (!depth && !stencil)
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, 800, 600, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
	else // Using both a stencil and depth test, needs special format arguments
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}


int main()
{
	Window* win = new Window(800, 600, "yoo");

	std::cout << "opengl - " << glGetString(GL_VERSION) << std::endl;
	glfwSwapInterval(1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GlProgram lightingShader("./shaders/basic_lighting.vs", "./shaders/basic_lighting.frag");
	GlProgram  basicShader("./shaders/basic.vs", "./shaders/basic.frag");
	GlProgram posteffect("./shaders/posteffect.vs", "./shaders/posteffect.frag");
	GlProgram basicposteffect("./shaders/basicposteffect.vs", "./shaders/basicposteffect.frag");
	//	Model nanosuit("./models/nanosuit/nanosuit.obj");
	Model cube("./models/cube.obj");

	FlyCamera camera(glm::vec3(0, 0, 3), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1), win);

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	FrameBuffer pstef(win->getWidth(), win->getHeight());




	GLfloat cubeVertices[] = {
		// Positions          // Texture Coords
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
	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);



	GLfloat planeVertices[] = {
		// Positions          // Normals         // Texture Coords
		8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
		-8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,

		8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
		-8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
		8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
	};
	// Setup plane VAO
	GLuint planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glBindVertexArray(0);






	Texture2D cubetexture("./textures/wall.jpg");
	Texture2D  planetexture("./textures/wood.jpg");
	
	std::vector<const char *> cubefaces;
	cubefaces.push_back("./textures/cubeMaps/hw_lagoon/lagoon_bk.tga");
	cubefaces.push_back("./textures/cubeMaps/hw_lagoon/lagoon_dn.tga");
	cubefaces.push_back("./textures/cubeMaps/hw_lagoon/lagoon_ft.tga");
	cubefaces.push_back("./textures/cubeMaps/hw_lagoon/lagoon_lf.tga");
	cubefaces.push_back("./textures/cubeMaps/hw_lagoon/lagoon_rt.tga");
	cubefaces.push_back("./textures/cubeMaps/hw_lagoon/lagoon_up.tga");
	vector<const char*> faces;
	faces.push_back("./textures/cubeMaps/skybox/right.jpg");
	faces.push_back("./textures/cubeMaps/skybox/left.jpg");
	faces.push_back("./textures/cubeMaps/skybox/top.jpg");
	faces.push_back("./textures/cubeMaps/skybox/bottom.jpg");
	faces.push_back("./textures/cubeMaps/skybox/back.jpg");
	faces.push_back("./textures/cubeMaps/skybox/front.jpg");
	CubeMap cubemap(faces);


	while (!win->isClosed())
	{
		win->clear();

		static double fisttime = Time::getTime();
		if (Time::getTime() - fisttime >= 2.0) {
			std::cout << "FPS: " << Time::getFps() << std::endl;
			fisttime = Time::getTime();
		}
		pstef.bind();

		camera.updatePosition();
		//	lightingShader.use();

		glm::mat4  view, projection;
		projection = glm::perspective(glm::radians(camera.getZoom()), (float)win->getWidth() / (float)win->getHeight(), 0.1f, 100.0f);
		view = camera.getMatrix();

		cubemap.draw(projection, view);

		//lightingShader.setUniform("projection", projection);
		//lightingShader.setUniform("view", view);


		//glm::mat4 model = glm::translate(glm::vec3(0.0f, -1.75f, 0.0f)) *glm::scale(glm::vec3(0.2f, 0.2f, 0.2f));

	//	lightingShader.setUniform("viewPos", camera.getposition());

		basicShader.use();
		basicShader.setUniform("projection", projection);
		basicShader.setUniform("view", view);
		glm::mat4 model = glm::mat4();
		cubetexture.use(0);
		basicShader.setUniform("model", model);
		//cube.Draw(&basicShader);

		glBindVertexArray(cubeVAO);
		//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//// Floor
		//glBindVertexArray(floorVAO);
		//floortexture.use(0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glBindVertexArray(0);
		//basicShader.unuse();

		glBindVertexArray(planeVAO);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		/*	for (std::size_t i = 0; i < 2; i++)
			{
				const glm::vec3 & pos = glm::vec3(pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
				PointLight(glm::vec3(), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.2f, 0.2f, 0.2f),
					glm::vec3(0.5, 0.5, 0.5), glm::vec3(1.0f, 1.0f, 1.0f), pos, 1.0f, 0.032, 0.09, &lightingShader);

				glm::mat4 pos_mat = glm::translate(pos) * glm::scale(glm::vec3(0.2, 0.2, 0.2));
				lightingShader.setUniform("model", pos_mat);
				cube.Draw(&lightingShader);
			}

			DirectionLight dirlight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), &lightingShader);

			lightingShader.setUniform("material.shininess", 32.f);

			lightingShader.setUniform("model", model);
			nanosuit.Draw(&lightingShader);


			lightingShader.unuse();*/


		pstef.unbind();
		pstef.draw(&posteffect);


		if (win->isKeyPressed(GLFW_KEY_B)) {
			pstef.draw(&posteffect);
		}
		else
		{
			pstef.draw(&basicposteffect);
		}


		win->update();
	}

	delete win;
	return 0;
}


