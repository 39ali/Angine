#pragma once
#include <angine.h>


class GameObject
{
public:
	GameObject();
	GameObject(const glm::vec2& _pos, const glm::vec2& _size, const glm::vec2& _velocity
		, const glm::vec3& _color, const Texture2D& _texture);
	virtual void draw(SpriteRenderer* renderer);
public:
	glm::vec2 position, size , velocity;
	glm::vec3 color;
	float rotation;
	
	bool isSolid;
	bool isdestroyed;
	Texture2D texture;



};