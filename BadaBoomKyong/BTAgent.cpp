#include "BTAgent.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

BTAgent::BTAgent(Boss* _boss, BTNode* _node)
	:m_pBoss(_boss)
	,m_pRoot(_node)
{
}

BTAgent::~BTAgent()
{
}

void BTAgent::SendMsg(const std::string& _name, bool _isInterrupt)
{
	m_MsgQueue.push(AgentMessage(_name, _isInterrupt));
}

void BTAgent::Update()
{
	if (m_MsgQueue.empty())
		return;
	AgentMessage msg = m_MsgQueue.front();
	m_MsgQueue.pop();

	if (m_eNodeLastState == BTNodeState::RUNNING && msg.m_bIsInterrupt)
	{
#ifdef _DEBUG
		std::cout << "Interrupt Call" << std::endl;
#endif
		m_pRoot->Abort();
		m_eNodeLastState = BTNodeState::SUCCESS;
	}
	BTNodeState cur_state = m_pRoot->Tick();
	m_eNodeLastState = cur_state;
}
