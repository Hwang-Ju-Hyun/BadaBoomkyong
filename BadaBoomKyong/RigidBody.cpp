#include "RigidBody.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Serializer.h"
#include "TimeManager.h"
#include "Transform.h"
#include "Player.h"

RigidBody::RigidBody(GameObject* _owner)
	:MonoBehaviour(_owner)
{
	SetName(this->RigidBodyTypeName);
}

RigidBody::~RigidBody()
{
}

void RigidBody::SetVelocity(const glm::vec3& _vel)
{
	if (!m_bIsKinematic)
		m_vVelocity = _vel;
}

void RigidBody::AddImpulse(const glm::vec3& impulse)
{
	if (!m_bIsKinematic)
		jumpforce = impulse.y ; // 질량 고려
}

void RigidBody::Init()
{

}

void RigidBody::Update()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();

	if (!m_bIsKinematic)
	{		
		if (m_bIsGround)
		{
			m_vVelocity.y = 0.f;			
		}
		else 
		{			
			m_vVelocity.y -= m_fGravity * dt;
		
			if (m_vVelocity.y < m_fMaxFallSpeed)
				m_vVelocity.y = m_fMaxFallSpeed;			
		}

		
		Transform* transform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
		if (transform)
			transform->AddPosition(m_vVelocity * dt);		
	}
}

BaseRTTI* RigidBody::CreateRigidBodyComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(RigidBodyTypeName, new RigidBody(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void RigidBody::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto Iskinematic = iter_compData->find(KinematicName);
		m_bIsKinematic = Iskinematic->begin().value();

		auto gra = iter_compData->find(GravityName);
		m_fGravity = gra->begin().value();

		auto mass = iter_compData->find(MassName);
		m_fMass = mass->begin().value();
	}
}

json RigidBody::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = RigidBodyTypeName;

	json compData;
	compData[KinematicName] = { m_bIsKinematic };
	compData[GravityName] = { m_fGravity };
	compData[MassName] = { m_fMass };
	data[CompDataName] = compData;

	return data;
}
