#include "Wait.h"
#include "TimeManager.h"

Wait::Wait(float _time)    
    :m_fWaitTime(_time)
{
}

BTNodeState Wait::Enter(BlackBoard& _bb)
{
    return BTNodeState::RUNNING;
}

BTNodeState Wait::Update(BlackBoard& _bb)
{
    float dt = TimeManager::GetInstance()->GetDeltaTime();
    m_fAccTime += dt;
    if (m_fAccTime >= m_fWaitTime)
    {
        m_fAccTime = 0.f;
        return BTNodeState::SUCCESS;
    }
        
    return BTNodeState::RUNNING;
}

void Wait::Exit(BlackBoard& _bb)
{
    m_fAccTime = 0.f;
}

void Wait::Abort()
{
}
