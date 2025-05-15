#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <unordered_map>

class FactoryManager
{
public:
	SINGLETON(FactoryManager);
public:
    void Init();
};