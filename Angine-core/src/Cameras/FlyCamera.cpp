#include "FlyCamera.h"


FlyCamera::FlyCamera(const glm::vec3&  pos, const glm::vec3& up, const glm::vec3& right, const glm::vec3& front, const Window* win) :
	m_position(pos), m_up(up), m_right(right), m_front(front), m_window(win), m_speedAmount(1.5f), m_speed(0.0f)
{
	m_window->disableCursor();
	m_lastX = m_window->getWidth() / 2.f;
	m_lastY = m_window->getHeight() / 2.f;
	m_senitivity = 5;

}


FlyCamera::~FlyCamera()
{}



void FlyCamera::updatePosition()
{

	double x, y, offsetX, offsetY;
	m_window->getMousePos(x, y);

	offsetX = x - m_lastX;
	offsetY = m_lastY - y;

	m_lastX = (float)x;
	m_lastY = (float)y;

	offsetX *= m_senitivity;
	offsetY *= m_senitivity;

	m_yaw = std::fmod(m_yaw + (float)(offsetX *Time::getDeltaTime()), 360.0f);
	m_pitch += (float)(offsetY * Time::getDeltaTime());

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;


	glm::vec3 font;
	font.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	font.y = sin(glm::radians(m_pitch));
	font.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(font);


	m_speed = float(m_speedAmount * Time::getDeltaTime());
	if (m_window->isKeyPressed(GLFW_KEY_W))
		m_position += m_speed *m_front;

	if (m_window->isKeyPressed(GLFW_KEY_S))
		m_position -= m_front *m_speed;

	if (m_window->isKeyPressed(GLFW_KEY_A))
		m_position -= glm::normalize(glm::cross(m_front, m_up))*m_speed;
	if (m_window->isKeyPressed(GLFW_KEY_D))
		m_position += glm::normalize(glm::cross(m_front, m_up))*m_speed;


	m_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
}
