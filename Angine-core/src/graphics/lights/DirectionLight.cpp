#include "directionlight.h"

DirectionLight::DirectionLight(const glm::vec3& direction, const glm::vec3& color, const glm::vec3&  ambient, const glm::vec3& diffuse, const glm::vec3& specular, GlProgram* shader)
	: Light(direction, color, ambient, diffuse, specular, shader)
{

	m_shader->setUniform("dirLight.direction", m_direction);
	m_shader->setUniform("dirLight.ambient", m_ambient);
	m_shader->setUniform("dirLight.diffuse", m_diffuse);
	m_shader->setUniform("dirLight.specular", m_specular);
	m_shader->setUniform("lightColor", color);
};
DirectionLight::~DirectionLight() {};






