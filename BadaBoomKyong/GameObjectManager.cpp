#include "GameObjectManager.h"
#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include "ModelManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{	
}

//void GameObjectManager::Update()
//{
//	for (int i = 0;i < m_vGameObjects.size();i++)
//	{
//		if (m_vGameObjects[i]->GetActive())
//		{
//			m_vGameObjects[i]->SetAwakable(true);
//		}
//	}
//}

void GameObjectManager::Exit()
{
	for (auto obj : m_vGameObjects)
	{
		delete obj;
	}
	m_vGameObjects.clear();

	std::vector<GameObject*>temp = m_vGameObjects;
	temp.swap(m_vGameObjects);
}

size_t GameObjectManager::AssignObjectID(GameObject* _obj)
{
	int size = m_vGameObjects.size();
	size_t next_id=0;
	for (int i = 0;i <size-1;i++)
	{
		if (m_vGameObjects[i]->GetName() == _obj->GetName())
		{
			next_id = m_vGameObjects[i]->GetID() + 1;
			_obj->SetID(next_id);			
		}
	}
	return next_id;
}

void GameObjectManager::AddObject(GameObject* _obj)
{	
	m_vGameObjects.push_back(_obj);			
	size_t next_id=AssignObjectID(_obj);
	m_mapGameObject.insert({ {_obj->GetName(),next_id},_obj });
}

GameObject* GameObjectManager::FindObject(const std::string& _name, size_t _id)
{
	auto iter = m_mapGameObject.find({ _name,_id });
	if (iter != m_mapGameObject.end())
		return iter->second;
	return nullptr;	
}

GameObject* GameObjectManager::GetLastObject()
{
	int size = m_vGameObjects.size();
	assert(size > 0);
	return m_vGameObjects[size - 1];
}

void GameObjectManager::DeleteObject(const std::string& _name)
{
	for (auto iter = m_vGameObjects.begin();iter != m_vGameObjects.end();)
	{
		if ((*iter)->GetName() == _name)
		{
			delete (*iter);
			iter = m_vGameObjects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void GameObjectManager::DeleteObject(const std::string& _name, size_t _id)
{
	for (auto iter = m_vGameObjects.begin();iter != m_vGameObjects.end();)
	{
		if ((*iter)->GetName() == _name&&(*iter)->GetID()==_id)
		{
			delete (*iter);
			iter = m_vGameObjects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void GameObjectManager::DeleteAllObject()
{
	for (auto iter = m_vGameObjects.begin();iter != m_vGameObjects.end();)
	{
		if ((*iter) != nullptr)
		{
			delete (*iter);
			iter = m_vGameObjects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}