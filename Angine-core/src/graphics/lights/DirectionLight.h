#pragma once
#include "Light.h"
class DirectionLight : public Light
{
public:
	DirectionLight(const glm::vec3& direction, const glm::vec3& color, const glm::vec3&  ambient, const glm::vec3& diffuse, const glm::vec3& specular, GlProgram* shader);
	~DirectionLight();



};