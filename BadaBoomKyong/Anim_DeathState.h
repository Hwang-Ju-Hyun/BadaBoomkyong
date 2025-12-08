#pragma once
#include "Anim_IState.h"
#include "EventManager.h"
#include "AudioManager.h"
template<typename T>
class AnimDeathState :public AnimIState<T>
{
public:
    AnimDeathState() {}
    virtual ~AnimDeathState()override {}
public:
    virtual void Enter(T* _owner) override
    {        
        if constexpr (std::is_same<T, Player>::value)
        {
            AudioManager::GetInstance()->PlaySound("playerDeath", 1.0f);
        }
        _owner->GetAnimator()->ChangeAnimation("Death");
    }

    virtual void Update(T* _owner) override
    {                
        if (_owner->GetAnimator()->GetAnimation()->m_bLoopCount >= 1)
        {
            EventManager::GetInstance()->DeleteObject(_owner->GetOwner());
            //EventManager::GetInstance()->SetActiveFalse(_owner->GetOwner());
        }
    }

    virtual void Exit(T* _owner) override {}
};