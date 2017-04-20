#include "GameObject.h"



GameObject::GameObject()
	: position(0, 0), size(1, 1), velocity(0.0f), color(1.0f), rotation(0.0f), texture(Texture2D(""))
	, isSolid(false), isdestroyed(false) { }

GameObject::GameObject(const glm::vec2& _pos, const glm::vec2& _size, const  glm::vec2& _velocity
	, const glm::vec3& _color, const Texture2D& _texture) : position(_pos), size(_size), velocity(_velocity)
	, color(_color), texture(_texture), rotation(0), isSolid(false), isdestroyed(false)
{

}

void GameObject::draw(SpriteRenderer* renderer)
{
	renderer->draw(position, size, rotation, texture, color);
}