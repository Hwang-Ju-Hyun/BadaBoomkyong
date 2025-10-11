#pragma once

class BlackBoard;

enum class BTNodeState
{
	SUCCESS,
	FAILURE,
	RUNNING
};

class BTNode
{
public:
	virtual BTNodeState Enter(BlackBoard& _bb) = 0;
	virtual BTNodeState Tick(BlackBoard& _bb) = 0;
	virtual void Abort() = 0;
	virtual ~BTNode() {}
};