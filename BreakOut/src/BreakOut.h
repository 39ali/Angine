#pragma once
#include "angine.h"
#include "Level.h"
#include "Player.h"
#include "Ball.h"
#include "GameLogic.h"



class Game : public Angine
{
public:
	Game();
	~Game();

private:
	void init();
	void render();
	void update();
	void checkCollission();
	void reset() const;
private:
	SpriteRenderer* m_spriteRenderer;
	GlProgram * m_shader;
	Label* m_label;
	Level* m_lvl;
	Player* m_player;
	Ball* m_ball;

};
