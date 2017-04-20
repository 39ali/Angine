#include "GameLogic.h"


bool GameLogic::doCollision(GameObject& a, GameObject&b)  //rect collision
{
	bool x = a.position.x + a.size.x >= b.position.x &&
		b.position.x + b.size.x >= a.position.x;
	bool y = a.position.y + a.size.y >= b.position.y &&
		b.position.y + b.size.y >= a.position.y;
	return x&&y;
}

CollisionInfo GameLogic::doCircleCollision(Ball& a, GameObject&b)  //rect & circular collision
{
	glm::vec2 Circle_center(a.position + a.radius);

	glm::vec2 box_half(b.size.x / 2, b.size.y / 2);

	glm::vec2 box_center(
		b.position.x + box_half.x,
		b.position.y + box_half.y
	);

	glm::vec2 distance = Circle_center - box_center; // distance between two centers

	glm::vec2 clamped = glm::clamp(distance, -box_half, box_half);


	glm::vec2 closestP = box_center + clamped; // closest p to  circle 

	distance = closestP - Circle_center;
	if (glm::length(distance) <= a.radius)
	{
		return std::make_tuple(true, checkVectorDir(distance), distance);
	}
	else
	{
		return std::make_tuple(false, Direction::UP, glm::vec2(0.0f));
	}
}

Direction  GameLogic::checkVectorDir(const glm::vec2& vec)
{
	const static  glm::vec2 directions[4] = {
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, -1.0f),
		glm::vec2(1.0f, 0.0f),	// r
		glm::vec2(-1.0f, 0.0f)	// l
	};
	float max = 0.0f;
	uint best_match = -1;
	for (uint i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(vec), directions[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;


}


