#pragma once

class Monster;

class ITraceBehaviour
{
public:
	virtual void DoTraceBehaviour(Monster* _mon) = 0;
	virtual ~ITraceBehaviour() = default;
};