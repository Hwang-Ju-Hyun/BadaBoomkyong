#include "Monster.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Serializer.h"
#include "GeometryUtill.h"
#include "Collider.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"

Monster::Monster(GameObject* _owner)
	:MonoBehaviour(_owner)
{
	SetName(MonsterTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));

	m_pTransform->SetScale({ 50.f,50.f,0.f });
	m_pCollider->SetOffsetPosition({ 0.f,0.f,0.f });
	m_pCollider->SetScale({ m_pTransform->GetScale() });
}

Monster::~Monster()
{
}

void Monster::Init()
{
}

void Monster::Update()
{
}

void Monster::Exit()
{
}

void Monster::EnterCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::TEMP)
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
}

void Monster::OnCollision(Collider* _other)
{
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::TEMP)
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
}

void Monster::ExitCollision(Collider* _other)
{
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

	data[CompDataName] = compData;

	return data;
}
