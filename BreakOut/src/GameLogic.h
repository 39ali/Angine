#pragma once
#include "GameLogic.h"
#include "Ball.h"
#include <tuple>
#include "Player.h"

typedef unsigned int uint;
enum Direction
{
	UP, DOWN, LEFT, RIGHT
};
typedef std::tuple<bool, Direction, glm::vec2> CollisionInfo;

class GameLogic
{
public:
	GameLogic() = delete;
	~GameLogic() = delete;
	static	bool doCollision(GameObject& a, GameObject&b);
	static CollisionInfo  doCircleCollision(Ball& a, GameObject&b);
	static Direction checkVectorDir(const glm::vec2& vec);
};