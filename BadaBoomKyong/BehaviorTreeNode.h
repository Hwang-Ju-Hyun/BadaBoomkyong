#pragma once

enum class BTNodeState
{
	SUCCESS,
	FAILURE,
	RUNNING
};

class BTNode
{
public:
	virtual BTNodeState Enter() = 0;
	virtual BTNodeState Tick() = 0;
	virtual void Abort() = 0;
	virtual ~BTNode() {}
};