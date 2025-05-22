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

void GameObjectManager::AddObject(GameObject* _obj)
{	
	m_vGameObjects.push_back(_obj);
	if (m_vGameObjects.size() > 0)
	{
		if (m_vGameObjects.size() == 1)
		{
			m_vGameObjects[0]->SetID(m_uObjID);
			m_uObjID++;			
		}
		else
		{			
			for (int i = 1;i < m_vGameObjects.size();i++)
			{
				if (m_vGameObjects[i - 1]->GetName() == m_vGameObjects[i]->GetName())
				{
					m_vGameObjects[i]->SetID(m_uObjID);					
				}
				else
				{
					m_uObjID = 0;
					m_vGameObjects[i]->SetID(m_uObjID);
				}
				m_uObjID++;
			}
		}		
	}		
}

GameObject* GameObjectManager::FindObject(const std::string& _name)
{
	for (int i = 0;i < m_vGameObjects.size();i++)
	{
		if (m_vGameObjects[i]->GetName() == _name)
		{
			return m_vGameObjects[i];
		}
	}
	std::cout << _name << " is not exist in GameObjectVector : GameObjectManager::FindObject" << std::endl;
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
