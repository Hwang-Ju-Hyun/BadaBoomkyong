#pragma once
#include "Anim_IState.h"
class Monster;

template<typename T>
class AnimIdleState;  // Forward declaration

template<typename T>
class AnimDivingState :public AnimIState<T>
{
public:
	AnimDivingState() {}
	virtual ~AnimDivingState() override {}
public:
	virtual void Enter(T* _owner) override
	{
		_owner->GetAnimator()->ChangeAnimation("Attack_Dive_Loop");
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
			case MonsterAnimState::HURT:
				machine->ChangeAnimState(int(MonsterAnimState::HURT));
				break;
			case MonsterAnimState::DEATH:
				machine->ChangeAnimState(int(MonsterAnimState::DEATH));
				break;
			}
		}
	}
	virtual void Exit(T* _owner) override {}
};