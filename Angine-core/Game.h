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
private:
	GlProgram * m_simpleDepthShader;
	GlProgram* m_shader;
	GlProgram* m_quadShader;
	FlyCamera* m_camera;
	Label* m_label;

	Texture2D*  woodTexture;
	Shadow* shadowobj;

};



int main()
{
	Game game;
	game.start();

	return 0;
}