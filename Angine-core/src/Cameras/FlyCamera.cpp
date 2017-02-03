#include "FlyCamera.h"


FlyCamera::FlyCamera(const glm::vec3&  pos, const glm::vec3& up, const glm::vec3& right, const glm::vec3& front, const Window* win) :
	m_position(pos), m_up(up), m_right(right), m_front(front), m_window(win), m_speed(0.001f)
{


}


FlyCamera::~FlyCamera()
{}



void FlyCamera::updatePosition()
{
	if (m_window->isKeyPressed(GLFW_KEY_W))
		m_position += m_front * m_speed;

	if (m_window->isKeyPressed(GLFW_KEY_S))
		m_position -= m_front *m_speed;

	if (m_window->isKeyPressed(GLFW_KEY_A))
		m_position -= glm::normalize(glm::cross(m_front, m_up))*m_speed;
	if (m_window->isKeyPressed(GLFW_KEY_D))
		m_position += glm::normalize(glm::cross(m_front, m_up))*m_speed;


	m_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
}
