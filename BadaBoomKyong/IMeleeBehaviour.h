#pragma once

class Monster;

class IMeleeBehaviour
{
public:
	virtual void Init(Monster* _mon) = 0;
	virtual void DoMeleeBehaviour(Monster* _mon) = 0;	
	virtual ~IMeleeBehaviour() = default;
};