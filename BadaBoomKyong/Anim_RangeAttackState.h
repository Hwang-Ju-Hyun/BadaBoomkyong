#pragma once
#include "Anim_IState.h"
class Monster;

template<typename T>
class AnimIdleState;  // Forward declaration

template<typename T>
class AnimRangeAttackState : public AnimIState<T>
{
public:
    AnimRangeAttackState() {}
    virtual ~AnimRangeAttackState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("RangeAttack");
    }

    virtual void Update(T* _owner) override
    {
        if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimIdleState<T>());
                break;
            case MonsterAnimState::NORMAL_ATTACK:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimNormalAttackState<T>());
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
