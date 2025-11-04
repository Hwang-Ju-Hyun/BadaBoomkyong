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
#include "Anim_HurtState.h"
#include "Anim_LandState.h"

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
        AnimStateMachine<T>* machine = _owner->GetAnimStateMachine();
        if constexpr (std::is_same<T, Player>::value) 
        {            
            switch (_owner->GetCurrentState()) 
            {                
            case PlayerAnimState::JUMP:
                machine->ChangeAnimState(PlayerAnimState::JUMP);
                break;
            case PlayerAnimState::FALL:
                machine->ChangeAnimState(PlayerAnimState::FALL);
                break;
            case PlayerAnimState::TOSPRINT:
                machine->ChangeAnimState(PlayerAnimState::TOSPRINT);
                break;
            case PlayerAnimState::DASH:
                machine->ChangeAnimState(PlayerAnimState::DASH);
                break;
            case PlayerAnimState::HURT:
                machine->ChangeAnimState(PlayerAnimState::HURT);
                break;
            case PlayerAnimState::COMBO_ATTACK_1:
                machine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_1);
                break;
            case PlayerAnimState::HOLY_SLASH:
                machine->ChangeAnimState(PlayerAnimState::HOLY_SLASH);
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
            case MonsterAnimState::RANGE_ATTACK:
                machine->ChangeAnimState(int(MonsterAnimState::RANGE_ATTACK));
                break;
            case MonsterAnimState::NORMAL_ATTACK:
                machine->ChangeAnimState(int(MonsterAnimState::NORMAL_ATTACK));
                break;          
            case MonsterAnimState::HURT:
                machine->ChangeAnimState(int(MonsterAnimState::HURT));
                break;
            case MonsterAnimState::DEATH:
                machine->ChangeAnimState(int(MonsterAnimState::DEATH));
                break;    
            case MonsterAnimState::WALK:
                machine->ChangeAnimState(int(MonsterAnimState::WALK));
                break;
            //Flying demon
            case MonsterAnimState::TAKE_OFF:
                machine->ChangeAnimState(int(MonsterAnimState::TAKE_OFF));
                break;
            //Boss
            case MonsterAnimState::JUMP:
                machine->ChangeAnimState(int(MonsterAnimState::JUMP));
                break;
            case MonsterAnimState::FALL:
                machine->ChangeAnimState(int(MonsterAnimState::FALL));
                break;          
            case MonsterAnimState::DISAPPEAR:
                machine->ChangeAnimState(int(MonsterAnimState::DISAPPEAR));
                break;
            case MonsterAnimState::APPEAR:
                machine->ChangeAnimState(int(MonsterAnimState::APPEAR));
                break;
            }
        }        
    }

    virtual void Exit(T* _owner) override 
    {
        
    }
};
