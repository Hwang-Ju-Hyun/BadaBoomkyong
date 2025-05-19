#pragma once

#include <string>
#include "BaseRTTI.h"
#ifdef _DEBUG
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#endif // DEBUG

class GameObject;

class BaseComponent : public BaseRTTI
{
private:
	std::string m_sName="";
public:
	//todo 기본생성자 delete 원상복구 시키셈
	BaseComponent() = delete;
	BaseComponent(GameObject* _owner);
	virtual ~BaseComponent();
public:
	inline void SetName(const std::string& _name) { m_sName= _name; }
	inline const std::string& GetName()const { return m_sName; }
private:
	GameObject* m_pOwner=nullptr;
public:
	inline void SetOwner(GameObject* _obj) { m_pOwner = _obj; }
	inline GameObject* GetOwner()const { return m_pOwner; }
public:
	virtual void Init();
	virtual void Update();
	virtual void Exit();
public:
	static constexpr const char* CompDataName = "CompData";
public:
	BaseComponent* operator = (BaseComponent*) = delete;
public:
#ifdef _DEBUG
	virtual void EditInfoFromButton();
#endif // DEBUG
};