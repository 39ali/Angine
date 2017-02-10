#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "../graphics/Window.h"
#include "../graphics/Window.h"
class FlyCamera
{
public:

	FlyCamera(const glm::vec3&  pos, const glm::vec3& up, const glm::vec3& right, const glm::vec3& front, const Window*  win);
	~FlyCamera();
	void updatePosition();
	inline const glm::mat4& getMatrix() const { return m_matrix; }

private:
	glm::vec3 m_position;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_front;
	glm::mat4 m_matrix;
	const Window* m_window;
	float m_speed;
	float m_lastX;
	float m_lastY;
	float m_senitivity;
	float m_pitch;
	float m_yaw;
};