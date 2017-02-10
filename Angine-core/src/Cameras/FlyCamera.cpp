#include "FlyCamera.h"


FlyCamera::FlyCamera(const glm::vec3&  pos, const glm::vec3& up, const glm::vec3& right, const glm::vec3& front, const Window* win) :
	m_position(pos), m_up(up), m_right(right), m_front(front), m_window(win), m_speed(0.001f)
{
	m_window->disableCursor();
	m_lastX = m_window->getWidth() / 2;
	m_lastY = m_window->getHeight() / 2;
	m_senitivity = 0.3;

}


FlyCamera::~FlyCamera()
{}



void FlyCamera::updatePosition()
{
	
	double x, y, offsetX, offsetY;
	m_window->getMousePos(x, y);

	offsetX = x - m_lastX;
	offsetY = m_lastY - y;

	m_lastX = x;
	m_lastY = y;

	offsetX *= m_senitivity;
	offsetY *= m_senitivity;

	m_yaw += offsetX;
	m_pitch += offsetY;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;


	glm::vec3 font;
	font.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	font.y = sin(glm::radians(m_pitch));
	font.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(font);


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
