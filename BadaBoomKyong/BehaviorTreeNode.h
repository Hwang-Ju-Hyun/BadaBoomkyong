#pragma once

class BlackBoard;

enum class BTNodeState
{	
	SUCCESS,
	FAILURE,
	RUNNING,
	READY,
	EXIT
};

class BTNode
{
protected:
	BTNodeState m_eState = BTNodeState::READY;
public:
	virtual BTNodeState Enter(BlackBoard& _bb) = 0;
	virtual BTNodeState Update(BlackBoard& _bb) = 0;
	BTNodeState Tick(BlackBoard& _bb);
	virtual void Exit(BlackBoard& _bb) = 0;
	virtual void Abort() = 0;
	virtual ~BTNode() {}
};