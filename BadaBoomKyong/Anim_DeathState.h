#pragma once
#include "Anim_IState.h"

template<typename T>
class AnimDeathState :public AnimIState<T>
{
public:
    AnimDeathState() {}
    virtual ~AnimDeathState()override {}
public:
    virtual void Enter(T* _owner) override
    {
        _owner->GetAnimator()->ChangeAnimation("Death");
    }

    virtual void Update(T* _owner) override
    {        
    }

    virtual void Exit(T* _owner) override {}
};