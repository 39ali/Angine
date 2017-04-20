#include "Level.h"


Level::Level(const char * loc, float width, float height)
{

	init(loc, width, height);
}
Level::~Level() {}

void Level::draw(SpriteRenderer* renderer)
{
	for (auto gameobj : m_bricks)
	{
		if (!gameobj.isdestroyed) {
			gameobj.draw(renderer);
		}
	}

}


std::vector<std::vector<unsigned int>> Level::loadLevel(const char* loc)
{
	std::vector<std::vector<unsigned int>>level;
	std::string line;
	std::ifstream reader(loc);
	unsigned int  c;
	while (std::getline(reader, line))
	{
		std::istringstream sstream(line);
		std::vector<unsigned int> row;

		while (sstream >> c) {
			row.push_back(c);
		}
		level.push_back(row);
	}
	return level;
}
void Level::init(const char * loc, float width, float height)
{
	auto level = loadLevel(loc);
	m_bricks.clear();

	float unitwidth = width / level[0].size();
	float unitheight = height / level.size();
	Texture2D block_tex("textures/block.png");
	Texture2D solid_tex("textures/block_solid.png");


	for (int y = 0; y < level.size(); y++)
	{
		for (int x = 0; x < level[y].size(); x++)
		{
			GameObject gameobj;
			glm::vec2 pos(x*unitwidth, y*unitheight);
			glm::vec2 size(glm::vec2(unitwidth, unitheight));

			if (level[y][x] == 1) {
				gameobj = GameObject(pos, size,
					glm::vec2(0), glm::vec3(0.8f,0.8f,0.7f), solid_tex);
				gameobj.isSolid = true;
			}

			else if (level[y][x] == 2)
			{
				glm::vec3	color = glm::vec3(0.2f, 0.6f, 1.0f);
				gameobj = GameObject(pos, size,
					glm::vec2(0), color, block_tex);
			}
			else if (level[y][x] == 3)
			{
				glm::vec3 color = glm::vec3(0.0f, 0.7f, 0.0f);
				gameobj = GameObject(pos, size,
					glm::vec2(0), color, block_tex);
			}


			else if (level[y][x] == 4)
			{
				auto color = glm::vec3(0.8f, 0.8f, 0.4f);
				gameobj = GameObject(pos, size,
					glm::vec2(0), color, block_tex);
			}
			else if (level[y][x] == 5)
			{
				auto color = glm::vec3(1.0f, 0.5f, 0.0f);
				gameobj = GameObject(pos, size,
					glm::vec2(0), color, block_tex);
			}


			m_bricks.push_back(gameobj);
		}
	}
}