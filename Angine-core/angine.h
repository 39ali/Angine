#pragma once
#include "src\graphics\Window.h"
#include <iostream>
#include <glew\GL\glew.h>
#include "src\graphics\GlProgram.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "src\Cameras\FlyCamera.h"
#include "src\graphics\Label.h"
#include "src\graphics\Texture2D.h"
#include "src\graphics\Shadow.h"
class Angine
{
protected:
	Window* m_win;

	unsigned int m_updates;
	Angine()
	{

	}
	~Angine()
	{
		delete m_win;
	}

	virtual void init() = 0;
	virtual void render() = 0;
	virtual void update() {}
	virtual void tick() {}

	void run()
	{
		double beginTime = Time::getTime();
		double updateTime = 1.0 / 60.0f;
		double updateTimer = 0.0f;

		while (!m_win->isClosed())
		{
			m_win->clear();
			render();

			if (Time::getTime() - beginTime >= 1.0) {
				tick();
				beginTime = Time::getTime();
				m_updates = 0;
			}

			if (Time::getTime() - updateTimer >= updateTime) {
				m_updates++;
				update();
				updateTimer += updateTime;
			}

			m_win->update();
		}

	}
	void createWindow(int screenWidth, int screenHeight, std::string title) {
		m_win = new Window(screenWidth, screenHeight, title.c_str());
		std::cout << "opengl - " << glGetString(GL_VERSION) << std::endl;
	};
public:
	void start()
	{
		init();
		run();
	}

};