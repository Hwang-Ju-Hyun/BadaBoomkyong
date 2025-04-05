#pragma once
#include <string>

class GameObject;

class BaseComponent
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
	virtual void Init();
	virtual void Update();
	virtual void Exit();
public:
	BaseComponent* operator = (BaseComponent*) = delete;
};