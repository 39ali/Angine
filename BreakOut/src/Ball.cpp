#include "Ball.h"

Ball::Ball() {}

Ball::~Ball() {}

Ball::Ball(glm::vec2 pos, float _radius, glm::vec2 velocity, Texture2D texture) :
	GameObject(pos, glm::vec2(_radius * 2), velocity, glm::vec3(1.0f), texture), stuck(true), radius(_radius)
{
}
glm::vec2 Ball::move(Window* win, float playerposx, float playersizex)
{
	if (!stuck)
	{
		position += velocity* (float)Time::getDeltaTime();

		if (position.x <= 0.0f)
		{
			position.x = 0.0f;
			velocity.x = -velocity.x;
		}
		else if (position.x + size.x >= win->getWidth())
		{
			position.x = win->getWidth() - size.x;
			velocity.x = -velocity.x;
		}

		if (position.y <= 0.0f)
		{
			position.y = 0.0f;
			velocity.y = -velocity.y;
		}

	}

	else
	{
		position.x = (playerposx + (playersizex / 2.f) - radius);
	}
	if (win->isKeyPressed(GLFW_KEY_SPACE))
	{
		stuck = false;
	}
	return position;
}
void Ball::reset(const glm::vec2& _pos, const glm::vec2& _velocity)
{
	position = _pos;
	velocity = _velocity;
	stuck = true;

}
