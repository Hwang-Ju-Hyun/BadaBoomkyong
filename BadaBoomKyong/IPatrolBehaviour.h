#pragma once

class Monster;

class IPatrolBehaviour
{
public:
	virtual void Init(Monster* _mon) = 0;
	virtual void DoPatrolBehaviour(Monster* _mon) = 0;
	virtual ~IPatrolBehaviour() = default;
};