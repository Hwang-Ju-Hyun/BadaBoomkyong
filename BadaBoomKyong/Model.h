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
		glm::vec3 texcoord;
	};
private:
	std::vector<VertexAttribute> m_vVertices;
public:
	Model(const std::string& _name, MODEL_TYPE _modelType, GLenum _primitiveType, std::vector<VertexAttribute>&& _vertices);
	~Model();
private:
	std::string m_sName;
	enum MODEL_TYPE m_eModelType=MODEL_TYPE::TRIAGNLE;
	GLenum m_ePrimitiveType = -1;
	GLuint VBO=0;
	GLuint VAO=0;
private:
	void UploadBuffers();
public:		
	//Settor
	inline void SetModelType(const enum MODEL_TYPE _modelType) { m_eModelType = _modelType; }
	inline void SetPrimitiveType(const GLenum _primitiveType) { m_ePrimitiveType = _primitiveType; }	
public:
	//Gettor
	inline const enum MODEL_TYPE GetModelType()const { return m_eModelType; }	
	inline unsigned int GetVBO()const { return VBO; }
	inline unsigned int GetPositionCnt_of_VBO()const { return m_vVertices.size(); }
public:
	void Draw();
};