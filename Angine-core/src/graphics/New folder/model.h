#pragma once
#include"mesh.h"
#include <vector>
#include <string>
#include "GlProgram.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <soil\src\SOIL.h>
class Model
{
public:
	Model(const char* loc);
	~Model();
	void draw(GlProgram* shader)const;
private:

	void loadModel(const char* loc);
	void processNodes(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLint TextureFromFile(const char* path, std::string directory);
private:
	std::vector<Mesh> m_meshes;
	std::string m_dir;
	std::vector<Texture> m_loadedTextures;
};