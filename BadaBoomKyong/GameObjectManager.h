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
public:
	void Update();
	void Exit();
public:
	inline void AddObject(GameObject* _obj) { m_vGameObjects.push_back(_obj); int a = 0; }
	GameObject* FindObject(const std::string& _name);
	GameObject* GetLastObject();
	inline const std::vector<GameObject*>& GetAllObjects()const { return m_vGameObjects; }
	void DeleteObject(const std::string& _name);
	void DeleteAllObject();	
};

