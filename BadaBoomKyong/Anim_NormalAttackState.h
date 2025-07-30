#pragma once
#pragma once
#include "Anim_IState.h"

template<typename T>
class AnimIdleState;  // Forward declaration

template<typename T>
class AnimJumpState;  // Forward declaration

template<typename T>
class AnimFallState;  // Forward declaration

template<typename T>
class AnimDeathState;  // Forward declaration

template<typename T>
class AnimRangeAttackState;

#include "Monster.h"

template<typename T>
class AnimNormalAttackState : public AnimIState<T>
{
public:
    AnimNormalAttackState() {}
    virtual ~AnimNormalAttackState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        if constexpr (std::is_same<T, Monster>::value)
        {
            _owner->GetAnimator()->ChangeAnimation("NormalAttack_1");
            std::cout << "NormalATK Entered" << std::endl;
        }            
        else if constexpr (std::is_same<T, Player>::value)
        {
            _owner->GetAnimator()->ChangeAnimation("LightAttack");
            std::cout << "LightATK Entered" << std::endl;
        }
            
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
        else if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimIdleState<T>());
                break;
            case MonsterAnimState::RANGE_ATTACK:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimRangeAttackState<T>());
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
