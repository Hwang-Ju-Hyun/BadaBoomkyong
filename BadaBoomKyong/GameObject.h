#pragma once
#include <string>
#include "header.h"
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>

class Model;
class BaseComponent;

class GameObject
{
public:
	GameObject()=delete;
	GameObject(const std::string& _name="Default", MODEL_TYPE _modelType=MODEL_TYPE::TRIANGLE);
	~GameObject();
private:
	std::string m_sName="";
	Model* m_mModel = nullptr;	
public:
	//settor
	inline void SetName(const std::string& _name) { m_sName = _name; }	
	inline void SetModel(Model* _model) { m_mModel = _model; }
	void SetModelType(MODEL_TYPE _modelType);
	//gettor
	inline const std::string GetName() { return m_sName; }	
	inline Model* GetModel() { return m_mModel; }
	MODEL_TYPE GetModelType();
private:
	std::vector<BaseComponent*> m_vComponents;
	std::unordered_map<std::string, BaseComponent*> m_hashComponents;
public:
	void AddComponent(const std::string& _compName, BaseComponent* _comp);
	BaseComponent* FindComponent(const std::string& _compName);
	void DeleteComponent(const std::string& _compName);
};