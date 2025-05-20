#pragma once

class IPoolable
{
public:
	IPoolable() {}
	virtual ~IPoolable() = default;
public:
	virtual void Reset() = 0;
};