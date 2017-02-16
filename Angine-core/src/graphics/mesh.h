#pragma once
#include <glew\GL\glew.h>
#include <string>
#include <glm\gtx\transform.hpp>
#include <vector>
#include <cstddef>
#include "GlProgram.h"
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct Texture
{
	GLuint id;
	std::string type;
	std::string dir;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indicies, std::vector<Texture>& textures);
	~Mesh();
	void draw(GlProgram* shader)const;

private:
	void setup();

private:
	std::vector<Vertex> m_vertices;
	std::vector<GLuint> m_indices;
	std::vector<Texture> m_textures;
	GLuint m_VAO, m_VBO, m_EBO;

};