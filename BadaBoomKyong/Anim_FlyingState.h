#pragma once
#include "Anim_StateMachine.h"
#include "Monster.h"


template<typename T>
class AnimFlyingState : public AnimIState<T>
{
public:
    AnimFlyingState() {}
    virtual ~AnimFlyingState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("Flying");
    }

    virtual void Update(T* _owner) override
    {
        AnimStateMachine<Monster>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {                
            case MonsterAnimState::DIVE_START:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DIVE_START));
                break;
            case MonsterAnimState::HURT:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DIVE_START));
                break;            
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
