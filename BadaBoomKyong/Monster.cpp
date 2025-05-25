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

	Transform* player_trs = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
	assert(player_trs);
	m_vPlayerPosition = player_trs->GetPosition();

	m_pAI=dynamic_cast<AI*>(GetOwner()->FindComponent(AI::AITypeName));
	m_pAI->SetCurState(MONSTER_STATE::IDLE_STATE);
	assert(m_pAI != nullptr);

	m_pDetectRangeCol = new Collider(GetOwner());
	m_pDetectRangeCol->SetScale(m_vDetectRange);

	m_pRangedMoveAtkCol = new Collider(GetOwner());
	m_pRangedMoveAtkCol->SetScale(m_vRangedMoveAtkRange);

	m_pMeleeAtkRange = new Collider(GetOwner());
	m_pMeleeAtkRange->SetScale(m_vMeleeAtkRange);
}

Monster::~Monster()
{
}

void Monster::Init()
{	
}

void Monster::Update()
{		
	//인지범위
	/*if ((-1 * m_fDetectRange) + m_vPosition.x<=m_vPlayerPosition.x &&m_vPlayerPosition.x <= m_fDetectRange + m_vPosition.x)
	{
		m_pAI->ChangeState(MONSTER_STATE::RANGE_ATTACK_STATE);
	}*/		
}

void Monster::Exit()
{
	delete m_pDetectRangeCol;
	delete m_pRangedMoveAtkCol;
	delete m_pMeleeAtkRange;
}

void Monster::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLAYER)
		m_bCol = true;
}

void Monster::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
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
		m_vDetectRange.x = detect_ran->begin().value();
		m_vDetectRange.y = (detect_ran->begin()+1).value();
		m_vDetectRange.z = (detect_ran->begin()+2).value();

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
	compData[DetectRangeName] =			{ m_vDetectRange.x,m_vDetectRange.y,m_vDetectRange.z };
	compData[RangedMoveAtkRangeName] =	{ m_vRangedMoveAtkRange.x,m_vRangedMoveAtkRange.y,m_vRangedMoveAtkRange.z };
	compData[MeleeAtkRangeName] =		{ m_vMeleeAtkRange.x,m_vMeleeAtkRange.y,m_vMeleeAtkRange.z };

	data[CompDataName] = compData;

	return data;
}
