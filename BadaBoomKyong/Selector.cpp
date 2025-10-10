#include "Selector.h"

Selector::Selector(std::vector<BTNode*> _childNode)
	:m_vecChildNode(_childNode)
{
}

Selector::~Selector()
{
}

BTNodeState Selector::Enter()
{
	return BTNodeState();
}

BTNodeState Selector::Tick()
{
	while (m_iCurrent < m_vecChildNode.size())
	{
		BTNodeState state = m_vecChildNode[m_iCurrent]->Tick();
		if (state == BTNodeState::SUCCESS)
		{
			m_iCurrent = 0;
			return BTNodeState::SUCCESS;
		}
		if (state == BTNodeState::RUNNING)
		{			
			return BTNodeState::RUNNING;
		}
		m_iCurrent++;
	}
	m_iCurrent = 0;
	return BTNodeState::SUCCESS;
}

void Selector::Abort()
{
	if (m_iCurrent < m_vecChildNode.size())
	{
		m_vecChildNode[m_iCurrent]->Abort();
	}
	m_iCurrent = 0;
}
