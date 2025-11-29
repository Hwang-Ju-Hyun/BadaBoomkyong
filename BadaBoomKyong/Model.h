#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "header.h"
#include <glm.hpp>
#include <vector>

class Mesh;

class Model
{
public:
	Model(const std::string _name,MODEL_TYPE _modelType=MODEL_TYPE::CUBE,const std::string& _path="Nothing");
	~Model();
private:
	const std::string m_sName;
	const std::string m_sPath;
	MODEL_TYPE m_eModelType;
	std::vector<Mesh*> m_vMeshes;
public:
	int m_meshCnt = 0;
	void Draw();
public:
	inline std::vector<Mesh*> GetMeshes()const { return m_vMeshes; }
	inline void AddMesh(Mesh* _mesh) { m_vMeshes.push_back(_mesh); }
	inline const std::string& GetName()const { return m_sName; }
	inline MODEL_TYPE GetModelType()const { return m_eModelType; }
	inline const std::string GetPath()const { return m_sPath; }
};