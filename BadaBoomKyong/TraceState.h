#pragma once
#include "BaseState.h"
class TraceState :
    public BaseState
{
public:
    TraceState(MONSTER_STATE _state = MONSTER_STATE::TRACE_STATE);
    virtual ~TraceState()override;
public:
    virtual void Init(Monster* _mon)  override;
    virtual void Update(Monster* _mon)override;
    virtual void Exit(Monster* _mon)  override;
};

