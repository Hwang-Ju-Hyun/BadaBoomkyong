#pragma once
#pragma once
#include "Anim_IState.h"
#include "Player.h"
#include "Monster.h"
#include "EventManager.h"
#include "PlayerMelee.h"

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
        }            
        else if constexpr (std::is_same<T, Player>::value)
        {
            _owner->GetAnimator()->ChangeAnimation("ComboAtk_1");           
        }
            
    }

    virtual void Update(T* _owner) override
    {
        AnimStateMachine<T>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value)
        {
            switch (_owner->GetCurrentState())
            {    
            case PlayerAnimState::IDLE:
                machine->ChangeAnimState(PlayerAnimState::IDLE);
                break;
            case PlayerAnimState::COMBO_ATTACK_2:
                machine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_2);
                break;
            case PlayerAnimState::HURT:
                machine->ChangeAnimState(PlayerAnimState::HURT);
                break;
            case PlayerAnimState::DEATH:
                machine->ChangeAnimState(PlayerAnimState::DEATH);
                break;
            }
        }
        else if constexpr (std::is_same<T, Monster>::value)
        {
            switch (_owner->GetCurrentState())
            {
            case MonsterAnimState::IDLE:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::IDLE));
                break;
            case MonsterAnimState::RANGE_ATTACK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::RANGE_ATTACK));
                break;
            case MonsterAnimState::HURT:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::HURT));
                break;
            case MonsterAnimState::WALK:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::WALK));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(static_cast<int>(MonsterAnimState::DEATH));
                break;
            }
        }
    }

    virtual void Exit(T* _owner) override 
    {
        if constexpr (std::is_same<T, Player>::value)
        {
            PlayerMelee* melee = dynamic_cast<PlayerMelee*>(_owner->GetMelee());
            if (melee)
            {
                EventManager::GetInstance()->SetActiveFalse(melee->GetOwner());
            }            
        }
        std::cout << "combo1 exit" << std::endl;
    }
};
