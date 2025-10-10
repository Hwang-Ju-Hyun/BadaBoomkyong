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
	Boss* m_pBoss;//지금은 걍 boss로 두는데 원래는 monster로 두거나 gameobject로 둬야하는거 알지?
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

