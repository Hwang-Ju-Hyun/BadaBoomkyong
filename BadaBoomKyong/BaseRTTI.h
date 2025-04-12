#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

class BaseRTTI
{
public:
	BaseRTTI();
	virtual ~BaseRTTI();
public:
	virtual void LoadFromJson(const json& _str) = 0;
	virtual json SaveToJson(const json& _str) = 0;
};

