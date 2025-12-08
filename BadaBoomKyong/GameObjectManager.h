#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

class GameObject;
static int as = 0;

class GameObjectManager
{
public:
	SINGLETON(GameObjectManager);
private:
	std::vector<GameObject*> m_vGameObjects;
	std::map<std::pair<std::string, size_t>, GameObject*> m_mapGameObject;
private:
	size_t m_uObjID = 0;
public:
	void Awake();
	void Update();
	void Exit();
public:
	void AddObject(GameObject* _obj);
	GameObject* FindObject(const std::string& _name,size_t _id=0);
	int GetObjectNumber(const std::string& _name);
	GameObject* GetLastObject();
	inline const std::vector<GameObject*>& GetAllObjects()const { return m_vGameObjects; }
	void DeleteObject(const std::string& _name);
	void DeleteObject(const std::string& _name,size_t _id);
	void DeleteObject(GameObject* _obj);
	void DeleteAllObject();	
private:
	size_t AssignObjectID(GameObject* _obj);
public:
	
	inline void GameRestart() { std::cout << "RESTART!"<<as++ << std::endl; }
};

