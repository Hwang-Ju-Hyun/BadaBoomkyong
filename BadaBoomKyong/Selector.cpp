#include "Selector.h"

Selector::Selector(std::vector<BTNode*> _childNode)
	:m_vecChildNode(_childNode)
{
}

Selector::~Selector()
{
}

BTNodeState Selector::Enter(BlackBoard& _bb)
{
	return BTNodeState();
}
#include <iostream>
BTNodeState Selector::Update(BlackBoard& _bb)
{
	while (m_iCurrent < m_vecChildNode.size())
	{
		BTNodeState state = m_vecChildNode[m_iCurrent]->Tick(_bb);
#ifdef _DEBUG
		std::cout << "Current Node type: " << typeid(*m_vecChildNode[m_iCurrent]).name()
			<< ", State: " << static_cast<int>(state) << std::endl;
#endif
		if (state == BTNodeState::SUCCESS)
		{
			m_iCurrent = 0;
			return BTNodeState::SUCCESS;
		}
		if (state == BTNodeState::RUNNING)
		{			
			return BTNodeState::RUNNING;
		}
		//FAIL 
		m_iCurrent++;
	}
	m_iCurrent = 0;
	return BTNodeState::FAILURE;
}

void Selector::Exit(BlackBoard& _bb)
{
}

void Selector::Abort()
{
	if (m_iCurrent < m_vecChildNode.size())
	{
		m_vecChildNode[m_iCurrent]->Abort();
	}
	m_iCurrent = 0;
}
