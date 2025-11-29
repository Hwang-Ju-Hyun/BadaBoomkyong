#pragma once
#include <iostream>
template<typename T>
class AnimIState
{
public:
	AnimIState() {}
	virtual ~AnimIState() = default;
public:
	virtual void Enter(T* _owner) = 0;
	virtual void Update(T* _owner) = 0;
	virtual void Exit(T* _owner) = 0;
};