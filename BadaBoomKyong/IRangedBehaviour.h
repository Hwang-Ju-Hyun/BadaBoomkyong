#pragma once

class Monster;

class IRangedBehaviour
{
public:
	virtual void Init(Monster* _mon) = 0;
	virtual void DoRangedBehaviour(Monster* _mon) = 0;
	virtual ~IRangedBehaviour() = default;
};