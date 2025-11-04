#include "RandomSelector.h"
#include "MathUtil.h"
#include "BlackBoard.h"
#include "Boss.h"

RandomSelector::RandomSelector(std::vector<BTNode*> _childNode)
	:m_vecChildNode(_childNode)
{		
}

RandomSelector::~RandomSelector()
{
}

BTNodeState RandomSelector::Enter(BlackBoard& _bb)
{	
	m_vecShuffle = m_vecChildNode;
	MathUtil::GetInstance()->Shuffle(m_vecShuffle);
	m_iCurrent = 0;

	return BTNodeState::RUNNING;
}

BTNodeState RandomSelector::Update(BlackBoard& _bb)
{		
	while (m_iCurrent< m_vecShuffle.size())
	{		
		BTNodeState state = m_vecShuffle[m_iCurrent]->Tick(_bb);
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

void RandomSelector::Exit(BlackBoard& _bb)
{
	m_vecShuffle.clear();
}

void RandomSelector::Abort()
{
	if (m_iCurrent < m_vecChildNode.size())
	{
		m_vecChildNode[m_iCurrent]->Abort();
	}
}
