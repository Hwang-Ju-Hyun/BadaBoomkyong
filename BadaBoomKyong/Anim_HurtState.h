#pragma once
#include "Anim_IState.h"
#include "Player.h"
#include "Monster.h"

template<typename T>
class AnimHurtState : public AnimIState<T>
{
public:
    AnimHurtState() {}
    virtual ~AnimHurtState() override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("Hurt");
    }

    virtual void Update(T* _owner) override
    {
        if constexpr (std::is_same<T, Player>::value)
        {
            AnimStateMachine<Player>* player_machine = _owner->GetAnimStateMachine();
            switch (_owner->GetCurrentState())
            {            
            case PlayerAnimState::IDLE:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::IDLE));
                break;
            }
        }        
        if constexpr (std::is_same<T, Monster>::value)
        {
            AnimStateMachine<Monster>* mon_machine = _owner->GetAnimStateMachine();
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::IDLE));
                break;
            case MonsterAnimState::WALK:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::WALK));
                break;
            case MonsterAnimState::NORMAL_ATTACK:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::NORMAL_ATTACK));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
