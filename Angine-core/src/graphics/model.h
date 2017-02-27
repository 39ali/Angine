#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes
#include<glew\GL\glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <soil\src\SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "GlProgram.h"
#include "mesh.h"

GLint TextureFromFile(const char* path, string directory, bool gamma = false);

class Model
{
public:

	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;


	Model(string const & path, bool gamma = false) : gammaCorrection(gamma)
	{
		this->loadModel(path);
	}


	void Draw(GlProgram * shader)
	{
		for (GLuint i = 0; i < this->meshes.size(); i++)
			this->meshes[i].draw(shader);
	}

private:

	void loadModel(string path)
	{

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		
		this->directory = path.substr(0, path.find_last_of('/'));

		
		this->processNode(scene->mRootNode, scene);
	}

	
	void processNode(aiNode* node, const aiScene* scene)
	{
		
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
		

			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->processMesh(mesh, scene));
		}
	
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}

	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
	
		vector<Vertex> vertices;
		vector<GLuint> indices;
		vector<Texture> textures;

		
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; 

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
			// Normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.uv = vec;
			}
			else
				vertex.uv = glm::vec2(0.0f, 0.0f);
			//// Tangent
			//vector.x = mesh->mTangents[i].x;
			//vector.y = mesh->mTangents[i].y;
			//vector.z = mesh->mTangents[i].z;
			//vertex.Tangent = vector;
			//// Bitangent
			//vector.x = mesh->mBitangents[i].x;
			//vector.y = mesh->mBitangents[i].y;
			//vector.z = mesh->mBitangents[i].z;
			//vertex.Bitangent = vector;
			vertices.push_back(vertex);
		}

		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// Process materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			// 1. Diffuse maps
			vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. Specular maps
			vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. Normal maps
			std::vector<Texture> normalMaps = this->loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// 4. Height maps
			std::vector<Texture> heightMaps = this->loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		}

		
		return Mesh(vertices, indices, textures);
	}

	
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			GLboolean skip = false;
			for (GLuint j = 0; j < textures_loaded.size(); j++)
			{
				if (textures_loaded[j].dir == str.C_Str())
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{   
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory);
				texture.type = typeName;
				texture.dir = str.C_Str();
				textures.push_back(texture);
				this->textures_loaded.push_back(texture);  
			}
		}
		return textures;
	}
};




GLint TextureFromFile(const char* path, string directory, bool gamma)
{

	string filename = string(path);
	filename = directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, gamma ? GL_SRGB : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
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
