#include "PointLight.h"

int PointLight::m_pointLightNumb = 0;

PointLight::PointLight(const glm::vec3 & direction, const glm::vec3 & color, const glm::vec3& ambient,
	const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, const float constant
	, const float quadric, const float linear, GlProgram* glprogram)
	:Light(direction, color, ambient, diffuse, specular, glprogram)
{
	std::string s = "pointLights[" + std::to_string(m_pointLightNumb++) + "]";
	glprogram->setUniform((s + ".position").c_str(), position);
	glprogram->setUniform((s + ".constant").c_str(), constant);
	glprogram->setUniform((s + ".linear").c_str(), linear);
	glprogram->setUniform((s + ".quadratic").c_str(), quadric);
	glprogram->setUniform((s + ".ambient").c_str(), ambient);
	glprogram->setUniform((s + ".diffuse").c_str(), diffuse);
	glprogram->setUniform((s + ".specular").c_str(), specular);
};
PointLight::~PointLight() {};
