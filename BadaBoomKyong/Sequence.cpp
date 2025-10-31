#include "Sequence.h"

Sequence::Sequence(std::vector<BTNode*> _childNode)
	:m_vecChildNode(_childNode)
{
}

Sequence::~Sequence()
{
}

BTNodeState Sequence::Enter(BlackBoard& _bb)
{
	return BTNodeState::RUNNING;
}
#include <iostream>
BTNodeState Sequence::Update(BlackBoard& _bb)
{
	while (m_iCurrent < m_vecChildNode.size())
	{
		BTNodeState state = m_vecChildNode[m_iCurrent]->Tick(_bb);
#ifdef _DEBUG
		std::cout << "Current Node type: " << typeid(*m_vecChildNode[m_iCurrent]).name()
			<< ", State: " << static_cast<int>(state) << std::endl;
#endif
		if (state == BTNodeState::RUNNING)
			return BTNodeState::RUNNING;
		if (state == BTNodeState::FAILURE)
		{
			m_iCurrent = 0;
			return BTNodeState::FAILURE;
		}
		//STATE == SUCCESS
		m_iCurrent++;
	}
	m_iCurrent = 0;
	return BTNodeState::SUCCESS;
}

void Sequence::Exit(BlackBoard& _bb)
{
}

void Sequence::Abort()
{
	if (m_iCurrent < m_vecChildNode.size())
	{
		m_vecChildNode[m_iCurrent]->Abort();
	}
	m_iCurrent = 0;
}
