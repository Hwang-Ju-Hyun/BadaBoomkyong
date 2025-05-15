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
	Model* m_pModel = nullptr;
	bool m_bIs3D = false;
	GROUP_TYPE m_eGroup;
public:
	//settor
	inline void SetName(const std::string& _name) { m_sName = _name; }
	inline void SetModel(Model* _model) { m_pModel = _model; }
	inline void SetGroupType(GROUP_TYPE _groupType) { m_eGroup=_groupType; }
	inline void SetIs3D(bool _is3D) { m_bIs3D = _is3D; }
	void SetModelType(MODEL_TYPE _modelType);

	//gettor
	inline const std::string GetName() { return m_sName; }
	inline Model* GetModel() { return m_pModel; }
	inline const GROUP_TYPE GetGroupType() { return m_eGroup; }
	inline bool GetIs3D()const { return m_bIs3D; }
	MODEL_TYPE GetModelType();
private:
	std::vector<BaseComponent*> m_vComponents;
	std::unordered_map<std::string, BaseComponent*> m_hashComponents;
public:
	BaseComponent* AddComponent_and_Get(const std::string& _compName, BaseComponent* _comp);
	BaseComponent* FindComponent(const std::string& _compName);
	inline std::unordered_map<std::string, BaseComponent*> GetAllComponentsOfObj_Hash() { return m_hashComponents; }
	inline std::vector<BaseComponent*>  GetAllComponentsOfObj_vec() { return m_vComponents; }
	void DeleteComponent(const std::string& _compName);
private:
	bool m_bIsSerializable=true;
public:
	inline void SetIsSerializable(bool _savable) { m_bIsSerializable = _savable; }
	inline bool GetIsSerializable()const { return m_bIsSerializable; }
	//todo : 리펙토리해야함
public:
	bool m_bIsActive = true;
	inline void SetActive(bool _active) { m_bIsActive = _active; }
	inline bool GetActive()const { return m_bIsActive; }
	void reset() { return; }
};