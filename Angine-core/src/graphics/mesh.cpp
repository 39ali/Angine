#include "mesh.h"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	m_vertices = vertices;
	m_indices = indices;
	m_textures = textures;
	setup();

}
Mesh::~Mesh()
{

}
void Mesh::draw(GlProgram* shader)const
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string name = m_textures[i].type;
		std::string number = (name == "texture_diffuse") ? std::to_string(diffuseNr++) : std::to_string(specularNr++);

		glUniform1i(glGetUniformLocation(shader->getProgramId(), ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// Draw mesh
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setup()
{

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex),
		m_vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint),
		m_indices.data(), GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, uv));

	glBindVertexArray(0);

}