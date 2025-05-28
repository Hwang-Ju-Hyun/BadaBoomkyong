#include "Monster.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Serializer.h"
#include "GeometryUtill.h"
#include "Collider.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"
#include "Player.h"
#include "MathUtil.h"

Monster::Monster(GameObject* _owner)
	:MonoBehaviour(_owner)
{
	SetName(MonsterTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
	GameObject* player_obj=GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	m_pPlayer = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));

	assert(m_pTransform && m_pSprite&& m_pRigidBody && m_pCollider && m_pPlayer);

	m_fDirection = -1.f;
	m_vPosition = m_pTransform->GetPosition();	
	m_pCollider->SetScale({ m_pTransform->GetScale() });

	m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
	assert(m_pPlayerTransform);
	m_vPlayerPosition = m_pPlayerTransform->GetPosition();

	m_pAI=dynamic_cast<AI*>(GetOwner()->FindComponent(AI::AITypeName));	
	m_pAI->SetOwner(_owner);
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);

	assert(m_pAI != nullptr);	
}

Monster::~Monster()
{
}

void Monster::Init()
{	
}

#include "InputManager.h"
#include "ThrowingWeapon.h"
#include "EventManager.h"
void Monster::Update()
{		
	//인지범위
	auto math = MathUtil::GetInstance();
	m_vPosition = m_pTransform->GetPosition();
	m_vPlayerPosition = m_pPlayerTransform->GetPosition();

	float dist = math->DistanceBetweenPoints(m_vPosition, m_vPlayerPosition);
	if (dist <= m_fDetectRange)
	{
		m_pAI->ChangeState(MONSTER_STATE::RANGE_ATTACK_STATE);
	}
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_T) == GLFW_PRESS)
	{
		GameObject* a= GameObjectManager::GetInstance()->FindObject(ThrowingWeapon::ThrowingWeaponTypeName);
		ThrowingWeapon* b= static_cast<ThrowingWeapon*>(a->FindComponent(ThrowingWeapon::ThrowingWeaponTypeName));			
		EventManager::GetInstance()->SetActiveTrue(a);
	}
}

void Monster::Exit()
{

}

void Monster::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
		SetIsGround(true);
	}
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = true;
}

void Monster::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
		SetIsGround(true);
	}
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = true;
}

void Monster::ExitCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = false;
}

BaseRTTI* Monster::CreateMonsterComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(MonsterTypeName, new Monster(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void Monster::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto speed = iter_compData->find(SpeedName);
		m_fSpeed = speed->begin().value();

		auto jump = iter_compData->find(JumpForceName);
		m_fJumpImpulse = jump->begin().value();

		auto detect_ran = iter_compData->find(DetectRangeName);
		m_fDetectRange = detect_ran->begin().value();		

		auto ranged_move_ran = iter_compData->find(RangedMoveAtkRangeName);
		m_vRangedMoveAtkRange.x = ranged_move_ran->begin().value();
		m_vRangedMoveAtkRange.y = (ranged_move_ran->begin()+1).value();
		m_vRangedMoveAtkRange.z = (ranged_move_ran->begin()+2).value();

		auto melee_ran = iter_compData->find(MeleeAtkRangeName);
		m_vMeleeAtkRange.x = melee_ran->begin().value();
		m_vMeleeAtkRange.y = (melee_ran->begin()+1).value();
		m_vMeleeAtkRange.z = (melee_ran->begin()+2).value();
	}
}

json Monster::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = MonsterTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpImpulse;
	compData[DetectRangeName] =			m_fDetectRange;
	compData[RangedMoveAtkRangeName] =	{ m_vRangedMoveAtkRange.x,m_vRangedMoveAtkRange.y,m_vRangedMoveAtkRange.z };
	compData[MeleeAtkRangeName] =		{ m_vMeleeAtkRange.x,m_vMeleeAtkRange.y,m_vMeleeAtkRange.z };

	data[CompDataName] = compData;

	return data;
}
