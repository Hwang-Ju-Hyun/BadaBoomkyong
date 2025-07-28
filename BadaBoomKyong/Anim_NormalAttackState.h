#pragma once
#pragma once
#include "Anim_IState.h"

template<typename T>
class AnimIdleState;  // Forward declaration

template<typename T>
class AnimNormalAttackState : public AnimIState<T>
{
public:
    AnimNormalAttackState() {}
    virtual ~AnimNormalAttackState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("LightAttack");
    }

    virtual void Update(T* _owner) override
    {
        if constexpr (std::is_same<T, Player>::value)
        {
            switch (_owner->GetCurrentState())
            {    
            case PlayerAnimState::IDLE:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimIdleState<T>());
                break;
            case PlayerAnimState::DEATH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDeathState<T>());
                break;
            }
        }        
    }

    virtual void Exit(T* _owner) override {}
};
