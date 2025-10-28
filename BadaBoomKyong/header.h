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
	CUSTOM_MODEL=6,
	SKY_BOX=7,
	LAST
};

enum class GROUP_TYPE
{
	DEFAULT = 0,
	PLAYER = 1,
	BULLET = 2,
	MONSTER = 3,
	PLATFORM =4,
	MELEE=5,
	PORTAL=6,
	
	LAST
};

enum class SHADER_REF
{
	TWO_DIMENSIONS = 0,
	THREE_DIMENSIONS = 1,
	SKYBOX,
	PARTICLES,
	SHADER_REF_LAST
	
};

enum class BULLET_TYPE
{
	PISTOL = 0,
	MACHINE_GUN = 1,	
	CURSEDEMON_FIREBALL,
	BOSS_RANGE,
	BULLET_LAST
};

enum class STAGE_TYPE
{
	STAGE_TEST=0,
	STAGE_01=1,
	STAGE_02,
	STAGE_03
};

enum class MONSTER_STATE
{
	IDLE_STATE=0,
	PATROL_STATE,
	TRACE_STATE,
	MELEE_ATTACK_STATE,
	RANGE_ATTACK_STATE,	
	DEAD_STATE,
	LAST
};

enum class MONSTER_TYPE
{
	MONSTER_TEMP=0
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT, 
	LEVEL_CHANGE,
	ACTIVE_TRUE,
	ACTIVE_FALSE,	

	LAST
};

enum class ParticleEffectType
{
	HOLY_SLASH=0,
	LAST
};


static const float g_epsilon = 0.001f;
static const float PI = 3.141592;