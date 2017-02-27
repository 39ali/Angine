#include "model.h"

Model::Model(const char * loc)
{
	loadModel(loc);
};

Model::~Model()
{

};

void Model::draw(GlProgram* shader)const
{
	for (std::size_t i = 0; i <3; i++)
	{
		m_meshes[i].draw(shader);
		m_meshes[i].draw(shader);
	
	}
};

void Model::loadModel(const char* loc)
{

	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(loc, aiProcess_Triangulate );

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	std::string m_S = loc;
	m_dir = m_S.substr(0, m_S.find_last_of('/'));

	processNodes(scene->mRootNode, scene);

}
void Model::processNodes(aiNode* node, const aiScene* scene)
{
	for (std::size_t i = 0; i < node->mNumMeshes; i++)
	{
		auto mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (std::size_t i = 0; i < node->mNumChildren; i++)
	{
		processNodes(node->mChildren[i], scene);
	}

}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (std::size_t i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vec;
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vertex.position = vec;

		glm::vec3 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		vertex.normal = normal;

		glm::vec2 uv;
		if (mesh->mTextureCoords[0])
		{
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.x = mesh->mTextureCoords[0][i].x;
			vertex.uv = uv;
		}
		else
		{
			vertex.uv = uv;
		}

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// 1. Diffuse maps
		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. Normal maps
		std::vector<Texture> normalMaps = this->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. Height maps
		std::vector<Texture> heightMaps = this->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	}


	return Mesh(vertices, indices, textures);

};
std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		bool skip = false;
		for (Texture t : m_loadedTextures) {
			if (m_loadedTextures[i].dir == str.C_Str())
			{
				skip = true;
				textures.push_back(t);
				break;
			}
		}
		if (!skip) {
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), m_dir);
			texture.type = typeName;
			texture.dir = str.C_Str();
			textures.push_back(texture);
			m_loadedTextures.push_back(texture);
		}
	}
	return textures;

};


GLint Model::TextureFromFile(const char* path, std::string directory)
{

	std::string filename(path);
	filename = directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
	{
		std::cout << "unable to load image" << ": " << filename << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;
}