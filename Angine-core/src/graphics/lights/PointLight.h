#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(const glm::vec3 & direction, const glm::vec3 & color, const glm::vec3& ambient,
		const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& position, const float constant
		, const float quadric, const float linear, GlProgram* glprogram);
	~PointLight();
private:
	static int m_pointLightNumb;

};