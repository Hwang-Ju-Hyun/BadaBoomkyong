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
        AnimStateMachine<Monster>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                machine->ChangeAnimState(int(MonsterAnimState::IDLE));
                break;
            case MonsterAnimState::NORMAL_ATTACK:
                machine->ChangeAnimState(int(MonsterAnimState::NORMAL_ATTACK));
                break;
            case MonsterAnimState::WALK:
                machine->ChangeAnimState(int(MonsterAnimState::WALK));
                break;
            case MonsterAnimState::APPEAR:
                machine->ChangeAnimState(int(MonsterAnimState::APPEAR));
                break;
            case MonsterAnimState::DISAPPEAR:
                machine->ChangeAnimState(int(MonsterAnimState::DISAPPEAR));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(int(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
