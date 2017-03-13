#pragma once
#include <glm\glm.hpp>
#include "../GlProgram.h"
class Light
{
public:
	Light(const glm::vec3 & direction, const glm::vec3 & color, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, GlProgram* glprogram)
		:m_direction(direction), m_color(color), m_shader(glprogram)
	{};
	~Light() {};

protected:
	glm::vec3 m_direction;
	glm::vec3 m_color;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	GlProgram * m_shader;
};