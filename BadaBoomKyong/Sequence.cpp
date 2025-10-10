#include "Sequence.h"

Sequence::Sequence(std::vector<BTNode*> _childNode)
	:m_vecChildNode(_childNode)
{
}

Sequence::~Sequence()
{
}

BTNodeState Sequence::Enter()
{
	return BTNodeState();
}

BTNodeState Sequence::Tick()
{
	while (m_iCurrent < m_vecChildNode.size())
	{
		BTNodeState state = m_vecChildNode[m_iCurrent]->Tick();
		if (state == BTNodeState::RUNNING)
			return BTNodeState::RUNNING;
		if (state == BTNodeState::FAILURE)
		{
			m_iCurrent = 0;
			return BTNodeState::FAILURE;
		}
		m_iCurrent++;
	}
	m_iCurrent = 0;
	return BTNodeState::SUCCESS;
}

void Sequence::Abort()
{
	if (m_iCurrent < m_vecChildNode.size())
	{
		m_vecChildNode[m_iCurrent]->Abort();
	}
	m_iCurrent = 0;
}
