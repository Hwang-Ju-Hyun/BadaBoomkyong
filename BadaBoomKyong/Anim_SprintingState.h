#pragma once
#include "Anim_IState.h"
#include "Anim_SprintAttackState.h"

template<typename T>
class AnimDashState;  // Forward declaration
template<typename T>
class AnimIdleState;  // Forward declaration
template<typename T>
class AnimDeathState;  // Forward declaration

template<typename T>
class AnimSprintingState : public AnimIState<T>
{
public:
    AnimSprintingState() {}
    virtual ~AnimSprintingState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("Sprinting");
    }

    virtual void Update(T* _owner) override
    {
        AnimStateMachine<Player>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case PlayerAnimState::IDLE:
                machine->ChangeAnimState(PlayerAnimState::IDLE);
                break;         
            case PlayerAnimState::DASH:
                machine->ChangeAnimState(PlayerAnimState::DASH);
                break;
            case PlayerAnimState::HURT:
                machine->ChangeAnimState(PlayerAnimState::HURT);
                break;
            case  PlayerAnimState::RUN_ATTACK:
                machine->ChangeAnimState(PlayerAnimState::RUN_ATTACK);
                break;
            case  PlayerAnimState::JUMP_ATTACK:
                machine->ChangeAnimState(PlayerAnimState::JUMP_ATTACK);
                break;
            case  PlayerAnimState::JUMP:
                machine->ChangeAnimState(PlayerAnimState::JUMP);
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(PlayerAnimState::DEATH);
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
