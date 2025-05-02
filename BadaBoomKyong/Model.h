#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "header.h"
#include <glm.hpp>
#include <vector>

class Model
{
public:
	struct VertexAttribute
	{
	public:
		glm::vec3 position;
		glm::vec2 texcoord;
		glm::vec3 normals;
	};
private:
	std::vector<VertexAttribute> m_vVertices;
	std::vector<unsigned int> m_vIndices;	
	std::vector<glm::vec3> m_vNormals;
public:
	Model(const std::string& _name, MODEL_TYPE _modelType, GLenum _primitiveType, std::vector<VertexAttribute>&& _vertices, std::vector<unsigned int>&& _indices = { 0 });
	~Model();
private:
	std::string m_sName;
	enum MODEL_TYPE m_eModelType=MODEL_TYPE::TRIANGLE;
	GLenum m_ePrimitiveType = -1;
	GLuint VBO=0;
	GLuint VAO=0;
	GLuint EBO = 0;
	bool m_bEBO=false;
private:
	void UploadBuffers();
public:		
	//Settor
	inline void SetModelType(const enum MODEL_TYPE _modelType) { m_eModelType = _modelType; }
	inline void SetPrimitiveType(const GLenum _primitiveType) { m_ePrimitiveType = _primitiveType; }	
public:
	//Gettor
	inline const std::string& GetName() { return m_sName; }
	inline const enum MODEL_TYPE GetModelType()const { return m_eModelType; }	
	inline size_t GetVBO()const { return VBO; }
	inline size_t GetPositionCnt_of_VBO()const { return m_vVertices.size(); }
	inline std::vector<VertexAttribute> GetVertices()const { return m_vVertices; }
public:
	void Draw();
};