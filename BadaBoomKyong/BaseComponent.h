#pragma once
#include <cstring>

class GameObject;

class BaseComponent
{
private:
	char* m_sName;	
public:
	BaseComponent() = delete;
	BaseComponent(GameObject* _owner);
	virtual ~BaseComponent();
public:
	inline void SetName(const char* _name) { strcpy(m_sName, _name); }
	inline const char* GetName()const { return m_sName; }
private:
	GameObject* m_pOwner=nullptr;
public:
	virtual void Init();
	virtual void Update();
	virtual void Exit();
public:
	BaseComponent* operator = (BaseComponent*) = delete;
};