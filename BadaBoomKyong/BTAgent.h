#pragma once
#include <string>
#include <queue>
#include "BehaviorTreeNode.h"

class Boss;

struct AgentMessage
{	
public:
	bool m_bIsInterrupt;
	std::string name;
public:
	AgentMessage(const std::string& _msg,bool _interrupt) : name(_msg), m_bIsInterrupt(_interrupt){}
};

class BTAgent
{	
private:
	Boss* m_pBoss;//������ �� boss�� �δµ� ������ monster�� �ΰų� gameobject�� �־��ϴ°� ����?
	BTNode* m_pRoot;
private:
	std::queue<AgentMessage> m_MsgQueue;
	BTNodeState m_eNodeLastState = BTNodeState::SUCCESS;
public:
	BTAgent(Boss* _boss, BTNode* _node);
	~BTAgent();
public:
	void SendMsg(const std::string& _name, bool _isInterrupt = false);
	void Update();
};

