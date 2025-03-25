#pragma once
#include <string>
#include "header.h"

class Model
{
public:
	Model();
	~Model();
private:
	std::string m_sName = "Default";
	enum MODEL_TYPE m_eModelType=MODEL_TYPE::TRIAGNLE;
private:
	unsigned int m_iVBO;
public:
	//Settor
	inline void SetModelName(const std::string& _name) { m_sName = _name; }
	inline void SetModelType(const enum MODEL_TYPE _modelType) { m_eModelType = _modelType; }
	inline void SetVBO(const int _VBO) { m_iVBO = _VBO; }
public:
	//Gettor
	inline const enum MODEL_TYPE GetModelType()const { return m_eModelType; }
	inline const std::string& GetModelName() { return m_sName; }
	inline unsigned int GetVBO()const { return m_iVBO; }
public:
	void CreateAndGetModel(enum Model_TYPE _eModel);
};