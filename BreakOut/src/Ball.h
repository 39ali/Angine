#pragma once
#include "GameObject.h"
class Ball :public GameObject
{
public:
	Ball();
	~Ball();
	Ball(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D texture);
	glm::vec2 move(Window* win, float playerposx, float playersizex);
	void reset(const glm::vec2& position, const glm::vec2& velocity);

public:
	float radius;
	bool stuck;
};
