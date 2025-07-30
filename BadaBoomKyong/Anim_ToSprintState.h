#pragma once
#include "Anim_IState.h"
#include "Anim_SprintingState.h"

template<typename T>
class AnimIdleState;  // Forward declaration
template<typename T>
class AnimDeathState;  // Forward declaration
template<typename T>
class AnimDashState;  // Forward declaration

template<typename T>
class AnimToSprintState : public AnimIState<T>
{
public:
    AnimToSprintState() {}
    virtual ~AnimToSprintState() override {}
public:
    virtual void Enter(T* _owner) override 
    {
        _owner->GetAnimator()->ChangeAnimation("ToSprint");
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
            case PlayerAnimState::SPRINTING:
                machine->ChangeAnimState(PlayerAnimState::SPRINTING);
                break;
            case  PlayerAnimState::RUN_ATTACK:
                machine->ChangeAnimState(PlayerAnimState::RUN_ATTACK);
                break;
            case PlayerAnimState::DASH:
                machine->ChangeAnimState(PlayerAnimState::DASH);
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(PlayerAnimState::DEATH);
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
