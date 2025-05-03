#pragma once
#include <cassert>
#define ASSERT_MSG(cond, msg) assert((cond) && (msg))

enum MODEL_TYPE
{
	TRIANGLE = 0,
	CIRCLE = 1,
	RECTANGLE = 2,
	LINE=3,
	PLANE=4,
	CUBE=5,
	LAST
};

enum class GROUP_TYPE
{
	DEFAULT = 0,
	PLAYER = 1,
	TEMP = 2,

	LAST
};

enum class STAGE_TYPE
{
	STAGE_01=0,
	LAST
};

enum class SHADER_REF
{
	TWO_DIMENSIONS = 0,
	THREE_DIMENSIONS = 1,
	SHADER_REF_LAST
};