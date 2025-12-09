#pragma once
#include "Anim_StateMachine.h"
#include "Monster.h"
#include "AudioManager.h"

template<typename T>
class AnimTakeOffState : public AnimIState<T>
{
public:
    AnimTakeOffState() {}
    virtual ~AnimTakeOffState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        AudioManager::GetInstance()->PlaySound("TakeOff", 0.6f);
        _owner->GetAnimator()->ChangeAnimation("TakeOff");
    }

    virtual void Update(T* _owner) override
    {        
        AnimStateMachine<Monster>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Monster>::value)
        {            
            switch (_owner->GetCurrentState())
            {            
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            case MonsterAnimState::FLYING:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::FLYING));
                break;
            case MonsterAnimState::HURT:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::HURT));
                break;         
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
