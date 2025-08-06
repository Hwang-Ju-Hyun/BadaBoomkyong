#pragma once
#include "Anim_StateMachine.h"
#include "Monster.h"


template<typename T>
class AnimWalkState :public AnimIState<T>
{
public:
	AnimWalkState() {}
	virtual ~AnimWalkState()override{}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("Walk");
    }

    virtual void Update(T* _owner) override
    {        
        AnimStateMachine<Monster>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::IDLE));
                break;
            case MonsterAnimState::NORMAL_ATTACK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::NORMAL_ATTACK));
                break;
            case MonsterAnimState::RANGE_ATTACK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::RANGE_ATTACK));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};