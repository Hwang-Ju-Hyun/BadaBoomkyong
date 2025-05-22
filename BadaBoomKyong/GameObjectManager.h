#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

class GameObject;

class GameObjectManager
{
public:
	SINGLETON(GameObjectManager);
private:
	std::vector<GameObject*> m_vGameObjects;
private:
	size_t m_uObjID = 0;
public:
	void Update();
	void Exit();
public:
	void AddObject(GameObject* _obj);
	GameObject* FindObject(const std::string& _name);
	GameObject* GetLastObject();
	inline const std::vector<GameObject*>& GetAllObjects()const { return m_vGameObjects; }
	void DeleteObject(const std::string& _name);
	void DeleteAllObject();	
};

