#pragma once
#include "Anim_IState.h"
#include "Anim_JumpState.h"
#include "Anim_FallState.h"
#include "Anim_DeathState.h"
#include "Anim_NormalAttackState.h"
#include "Anim_ToSprintState.h"
#include "Anim_DashState.h"
#include "Player.h"  
#include "Monster.h"
#include "Anim_RangeAttackState.h"

template<typename T>
class AnimIdleState : public AnimIState<T>
{
public:
    AnimIdleState() {}
    virtual ~AnimIdleState() override {}
public:
    virtual void Enter(T* _owner) override 
    {
        _owner->GetAnimator()->ChangeAnimation("Idle");
    }

    virtual void Update(T* _owner) override 
    {
        if constexpr (std::is_same<T, Player>::value) 
        {
            switch (_owner->GetCurrentState()) 
            {
            case PlayerAnimState::JUMP:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimJumpState<T>());
                break;
            case PlayerAnimState::FALL:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimFallState<T>());
                break;
            case PlayerAnimState::TOSPRINT:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimToSprintState<T>());
                break;
            case PlayerAnimState::DASH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDashState<T>());
                break;
            case PlayerAnimState::ATTACK:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimNormalAttackState<T>());
                break;
            case PlayerAnimState::DEATH:
                _owner->GetAnimStateMachine()->ChangeAnimState(new AnimDeathState<T>());
                break;
            }
        }
        else if constexpr (std::is_same<T, Monster>::value)
        {
            AnimStateMachine<Monster>* machine = _owner->GetAnimStateMachine();
                switch (_owner->GetCurrentState())
            {           
            case MonsterAnimState::RANGE_ATTACK:
                machine->ChangeAnimState(new AnimRangeAttackState<T>());
                break;
            case MonsterAnimState::NORMAL_ATTACK:
                machine->ChangeAnimState(new AnimNormalAttackState<T>());
                break;
            case MonsterAnimState::DEATH:
                break;            
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
