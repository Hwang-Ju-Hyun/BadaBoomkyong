#pragma once
#include "BaseState.h"
class TraceState :
    public BaseState
{
public:
    TraceState(MONSTER_STATE _state = MONSTER_STATE::TRACE_STATE);
    virtual ~TraceState()override;
public:
    virtual void Init()  override;
    virtual void Update()override;
    virtual void Exit()  override;
};

