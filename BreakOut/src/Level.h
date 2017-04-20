#pragma once
#include <angine.h>
#include <vector>
#include "GameObject.h"
#include <fstream>
#include <sstream>

class Level
{
public:
	Level(const char * loc, float width, float height);
	~Level();
	void draw(SpriteRenderer* renderer);
	std::vector<GameObject> m_bricks;
private:
	void init(const char * loc, float width, float height);
	std::vector<std::vector<unsigned int>> loadLevel(const char* loc);
	


};