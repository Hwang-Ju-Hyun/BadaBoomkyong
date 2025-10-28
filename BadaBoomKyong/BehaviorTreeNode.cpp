#include "BehaviorTreeNode.h"
#include "BlackBoard.h"

BTNodeState BTNode::Tick(BlackBoard& _bb)
{
    if (m_eState == BTNodeState::READY)
    {
        m_eState = Enter(_bb);
        if (m_eState == BTNodeState::RUNNING)
            return BTNodeState::RUNNING;
    }
    BTNodeState state_result= m_eState;
    if(m_eState!=BTNodeState::FAILURE)
        state_result = Update(_bb);


    if (state_result != BTNodeState::RUNNING)
    {
        Exit(_bb);
        m_eState = BTNodeState::READY;
    }

    return state_result;
}
