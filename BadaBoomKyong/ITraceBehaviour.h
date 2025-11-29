#pragma once

class Monster;

class ITraceBehaviour
{
public:
	virtual void Init(Monster* _mon) = 0;
	virtual void DoTraceBehaviour(Monster* _mon) = 0;
	virtual ~ITraceBehaviour() = default;
};