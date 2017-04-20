#include "BreakOut.h"

Game::Game()
{
	createWindow(800, 600, "BreakOut", false);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_label = new Label("fonts/arial.ttf", "../Angine-core/shaders/textShader.vs", "../Angine-core/shaders/textShader.frag");
}
Game::~Game()
{
	delete m_spriteRenderer;
	delete  m_shader;

	delete m_label;
	delete m_lvl;
	delete m_player;
	delete m_ball;
}


#define INIT_ballVelocity glm::vec2 (1000.f, -3000.f)
#define INIT_playerSize   glm::vec2(100, 15)
#define INIT_playerPos    glm::vec2 ((m_win->getWidth() / 2) - (INIT_playerSize.x / 2.0f), m_win->getHeight() - INIT_playerSize.y)

#define  INIT_ballRadius    12.5f
#define  INIT_ballPos  glm::vec2(INIT_playerPos.x + (INIT_playerSize.x / 2) - INIT_ballRadius, INIT_playerPos.y - INIT_ballRadius * 2)

void Game::init()
{
	m_shader = new GlProgram("shaders/shader.vert", "shaders/shader.frag");

	m_spriteRenderer = new SpriteRenderer(m_shader);
	float w = static_cast<float>(m_win->getWidth());
	float h = static_cast<float>(m_win->getHeight());
	glm::mat4 orth = glm::ortho(0.0f, w, h, 0.0f, -1.0f, 1.0f);

	m_shader->use();
	m_shader->setUniform("projection", orth);
	m_shader->unuse();

	m_lvl = new Level("levels/1.lvl", 800, 250);

	Texture2D playertexture("textures/player.png");
	m_player = new Player(INIT_playerPos, INIT_playerSize, 5000.f, playertexture);

	Texture2D ballTexture("textures/ball.png");
	m_ball = new Ball(INIT_ballPos, INIT_ballRadius, INIT_ballVelocity, ballTexture);

}

void Game::render()
{
	m_lvl->draw(m_spriteRenderer);
	m_player->draw(m_spriteRenderer);
	m_ball->draw(m_spriteRenderer);
	if (m_ball->stuck) {
		m_label->drawString("Press Space to start", glm::vec2(m_win->getWidth() / 4.f, m_win->getHeight() / 2.f), 1, glm::vec3(1));
	}
}
void Game::update()
{
	m_player->processInput(m_win);
	m_ball->move(m_win, m_player->getPos().x, m_player->getSize().x);
	checkCollission();
	reset();
}

void Game::checkCollission()
{

	for (GameObject &box : m_lvl->m_bricks)
	{
		if (!box.isdestroyed)
		{

			CollisionInfo _collisionInfo = GameLogic::doCircleCollision(*m_ball, box);

			if (std::get<0>(_collisionInfo))
			{
				if (!box.isSolid)
					box.isdestroyed = true;

				Direction dir = std::get<1>(_collisionInfo);
				glm::vec2 diff_vec = std::get<2>(_collisionInfo);

				if (dir == LEFT || dir == RIGHT)
				{
					m_ball->velocity.x = -m_ball->velocity.x;
					float offset = m_ball->radius - std::abs(diff_vec.x);
					if (dir == LEFT)
						m_ball->position.x += offset;
					else //right
						m_ball->position.x -= offset;
				}
				else  //vertical movement
				{
					m_ball->velocity.y = -m_ball->velocity.y;
					float offsetY = m_ball->radius - std::abs(diff_vec.y);
					if (dir == Direction::UP)
						m_ball->position.y -= offsetY;
					else
						m_ball->position.y += offsetY;
				}

			}
		}
	}

	CollisionInfo colInfo = GameLogic::doCircleCollision(*m_ball, *m_player);
	if (!m_ball->stuck && std::get<0>(colInfo))
	{
		float playerCenter = m_player->position.x + m_player->size.x / 2;

		float distance = (m_ball->position.x + m_ball->radius) - playerCenter; // distance between player and ball center
		float percentage = distance / (m_player->size.x / 2);

		static	const float pushForce = 3.0f;
		glm::vec2 currentVelocity = m_ball->velocity;
		m_ball->velocity.x = INIT_ballVelocity.x * percentage * pushForce;
		m_ball->velocity.y = -1 * abs(m_ball->velocity.y);
		m_ball->velocity = glm::normalize(m_ball->velocity) * glm::length(currentVelocity);

	}
}

void Game::reset() const
{
	if (m_ball->position.y >= m_win->getHeight()) {
		m_player->position.x = INIT_playerPos.x;
		m_ball->reset(INIT_ballPos, INIT_ballVelocity);
	}
}


int main()
{
	int i = 0;
	Game game;
	game.start();
	return 0;
}