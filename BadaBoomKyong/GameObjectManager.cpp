#include "GameObjectManager.h"
#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include "ModelManager.h"
#include "ComponentManager.h"
#include "BaseComponent.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{	
}

void GameObjectManager::Awake()
{
	for(GameObject* obj : m_vGameObjects)
	{		
		for (BaseComponent* comp:obj->GetAllComponentsOfObj_vec())
		{
			if (!comp->m_bAwoken && comp->GetActive())
			{
				comp->Awake();
				comp->MarkAwoken(true);
			}
		}
	}
}

void GameObjectManager::Update()
{
	for (int i = 0;i < m_vGameObjects.size();i++)
	{
		if (m_vGameObjects[i]->GetActive())
		{
			for (auto comp : m_vGameObjects[i]->GetAllComponentsOfObj_vec())
			{	
				comp->Update();
			}
		}
	}
}

void GameObjectManager::Exit()
{
	DeleteAllObject();
	m_vGameObjects.clear();		
	m_mapGameObject.clear();

	std::vector<GameObject*>temp = m_vGameObjects;
	temp.swap(m_vGameObjects);
	std::map<std::pair<std::string, size_t>, GameObject*>map_temp = m_mapGameObject;
	map_temp.swap(m_mapGameObject);
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

int GameObjectManager::GetObjectNumber(const std::string& _name)
{
	int num = 0;
	for (int i = 0;i < m_vGameObjects.size();i++)
	{
		if (m_vGameObjects[i]->GetName() == _name)
			num++;
	}
	return num;
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