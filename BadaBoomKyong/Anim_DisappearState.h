#pragma once
#include "Anim_IState.h"

template<typename T>
class AnimFallState;  // Forward declaration

template<typename T>
class AnimDeathState;

template<typename T>
class AnimDisAppearState : public AnimIState<T>
{
public:
    AnimDisAppearState() {}
    virtual ~AnimDisAppearState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("Disappear");
    }

    virtual void Update(T* _owner) override
    {
        AnimStateMachine<T>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::IDLE));
                break;
            case MonsterAnimState::WALK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::WALK));
                break;
            case MonsterAnimState::APPEAR:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::APPEAR));
                break;
            case MonsterAnimState::FALL:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::FALL));
                break;
            case MonsterAnimState::JUMP_ATTACK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::JUMP_ATTACK));
                break;
            case MonsterAnimState::HURT:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::HURT));
                break;
            case MonsterAnimState::DASH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DASH));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
