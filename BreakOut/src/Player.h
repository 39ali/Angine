#pragma once
#include "GameObject.h"

class Player : public  GameObject
{
public:
	Player(const glm::vec2& _pos, const glm::vec2& _size, const float _velocity
		, const Texture2D& texture) : GameObject(_pos, _size, glm::vec2(_velocity, 0.f), glm::vec3(1.0f), texture)
	{

	}
	/*void draw(SpriteRenderer* renderer)
	{
		m_player.draw(renderer);
	}*/
	~Player() {}

	void processInput(Window * win)
	{
		float _velocity = velocity.x*(float)Time::getDeltaTime();
		if (win->isKeyPressed(GLFW_KEY_A))
		{
			if (position.x >= 0.0f)
			{
				position.x -= _velocity;
			}
		}
		if (win->isKeyPressed(GLFW_KEY_D))
		{
			if (position.x + size.x <= win->getWidth())
			{
				position.x += _velocity;
			}
		}
	}

	inline const glm::vec2& getPos() { return position; };
	inline const glm::vec2& getSize() { return size; };
};