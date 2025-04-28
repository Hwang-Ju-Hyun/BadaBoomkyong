#pragma once
#include <string>
#include "header.h"
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <vector>

class Model;
class BaseComponent;
class BaseRTTI;

class GameObject
{
public:
	GameObject() = delete;
	GameObject(const std::string& _name = "Default", MODEL_TYPE _modelType = MODEL_TYPE::TRIANGLE, GROUP_TYPE _groupType = GROUP_TYPE::DEFAULT);
	~GameObject();
private:
	std::string m_sName = "";
	Model* m_mModel = nullptr;
	GROUP_TYPE m_eGroup;
public:
	//settor
	inline void SetName(const std::string& _name) { m_sName = _name; }
	inline void SetModel(Model* _model) { m_mModel = _model; }
	inline void SetGroupType(GROUP_TYPE _groupType) { m_eGroup=_groupType; }
	void SetModelType(MODEL_TYPE _modelType);

	//gettor
	inline const std::string GetName() { return m_sName; }
	inline Model* GetModel() { return m_mModel; }
	inline const GROUP_TYPE GetGroupType() { return m_eGroup; }
	MODEL_TYPE GetModelType();
private:
	std::vector<BaseComponent*> m_vComponents;
	std::unordered_map<std::string, BaseComponent*> m_hashComponents;
public:
	BaseComponent* AddComponent_and_Get(const std::string& _compName, BaseComponent* _comp);
	BaseComponent* FindComponent(const std::string& _compName);
	inline std::unordered_map<std::string, BaseComponent*> GetAllComponentsOfObj() { return m_hashComponents; }
	void DeleteComponent(const std::string& _compName);
};