#pragma once
#include <cassert>
#define ASSERT_MSG(cond, msg) assert((cond) && (msg))

enum MODEL_TYPE
{
	TRIANGLE = 0,
	CIRCLE = 1,
	RECTANGLE = 2,
	LINE=3,
	LAST
};