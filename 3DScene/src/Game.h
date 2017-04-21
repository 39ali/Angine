#pragma once
#include "angine.h"
class Game :public Angine
{
public:
	Game();
	~Game();
private:
	virtual void init();
	virtual void  render();
	virtual void update();
	virtual void tick();
	void initgl();
	void renderScene(GlProgram &shader, bool depthRender = true);
	void RenderQuad();
	void RenderCube();
private:
	GlProgram * m_simpleDepthShader;
	GlProgram* m_shader;
	GlProgram* m_quadShader;
	FlyCamera* m_camera;
	Label* m_label;

	Texture2D*  m_woodTexture, *m_wallTexture;
	Shadow* shadowobj;
	GLuint m_planeVBO, m_planeVAO, m_quadVAO, m_quadVBO, m_cubeVAO, m_cubeVBO;
};


int main()
{
	Game game;
	game.start();

	return 0;
}