#pragma once
#include <string>
#include "BaseRTTI.h"

class GameObject;

class BaseComponent : public BaseRTTI
{
private:
	std::string m_sName="";
public:
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
	BaseComponent* operator = (BaseComponent*) = delete;
};