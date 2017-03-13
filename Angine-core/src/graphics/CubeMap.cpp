#include"CubeMap.h"
#include <iostream>
CubeMap::CubeMap(const std::vector<const char*>& Cubemaps)
{
	loadCubeMap(Cubemaps);
	loadVert();
	m_shader = new GlProgram("./shaders/cubemap.vs", "./shaders/cubemap.frag");
};

CubeMap::~CubeMap()
{

	delete m_shader;
	glDeleteTextures(1, &m_textureID);
};

void CubeMap::loadCubeMap(const std::vector<const char*>& Cubemaps)
{
	glGenTextures(1, &m_textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

	int width, height;
	unsigned char * image;
	for (size_t i = 0; i < Cubemaps.size(); i++)
	{
		image = SOIL_load_image(Cubemaps[i], &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
		{
			std::cout << "cube map loading error" << "/n";
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, GL_FALSE, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


};

void CubeMap::loadVert()
{
	GLfloat skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	GLuint vbo;
	glGenVertexArrays(1, &m_Vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(m_Vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (const void *)0);
	glBindVertexArray(0);



};

void CubeMap::draw(const glm::mat4& projection, const glm::mat4& view) const
{
	m_shader->use();

	m_shader->setUniform("projection", (glm::mat4&)projection);
	glm::mat4& viewmat3 = glm::mat4(glm::mat3(view));
	m_shader->setUniform("view", (glm::mat4&)viewmat3);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(m_shader->getProgramId(), "cubemap"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glDepthMask(GL_FALSE);
	glBindVertexArray(m_Vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	m_shader->unuse();
	glDepthMask(GL_TRUE);
};

