#pragma once
#include "Anim_IState.h"
#include "Player.h"
#include "Monster.h"
#include "AudioManager.h"
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
        AudioManager::GetInstance()->PlaySound("playerHurt", 1.0f);
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
            case PlayerAnimState::TOSPRINT:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::TOSPRINT));
                break;
            case PlayerAnimState::SPRINTING:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::SPRINTING));
                break;
            case PlayerAnimState::DASH:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::DASH));
                break;
            case PlayerAnimState::RUN_DASH:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::RUN_DASH));
                break;
            case PlayerAnimState::JUMP:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::JUMP));
                break;
            case PlayerAnimState::FALL:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::FALL));
                break;
            case PlayerAnimState::DEATH:
                player_machine->ChangeAnimState(static_cast<int>(PlayerAnimState::DEATH));
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
            case MonsterAnimState::TAKE_OFF:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::TAKE_OFF));
                break;
            case MonsterAnimState::DIVE_START:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DIVE_START));
                break;
            case MonsterAnimState::DIVING:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DIVING));
                break;
            case MonsterAnimState::NORMAL_ATTACK:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::NORMAL_ATTACK));
                break;
            case MonsterAnimState::DEATH:
                mon_machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override {}
};
