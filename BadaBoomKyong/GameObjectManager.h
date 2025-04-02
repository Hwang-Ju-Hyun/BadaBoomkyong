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
	inline void AddObject(GameObject* _obj) { m_vGameObjects.push_back(_obj); }
	GameObject* FindObject(const std::string& _name);
	inline const std::vector<GameObject*>& GetAllObjects()const { return m_vGameObjects; }
	void DeleteObject(const std::string& _name);
};

