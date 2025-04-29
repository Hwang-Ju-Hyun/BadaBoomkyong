#include "RigidBody.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Serializer.h"
#include "TimeManager.h"
#include "Transform.h"

RigidBody::RigidBody(GameObject* _owner)
	:BaseComponent(_owner)
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
		m_vVelocity += impulse / m_fMass; // 질량 고려
}

void RigidBody::Init()
{

}

void RigidBody::Update()
{
	if (m_bIsKinematic)
		return;
	double dt = TimeManager::GetInstance()->GetDeltaTime();
	
	if (m_bUseGravity)
		m_vAccelation.y -= m_fGravity;

	// 총 가속도 = 힘 + 자체 가속도
	glm::vec3 totalAccel = (m_vForce / m_fMass) + m_vAccelation;

	// 속도 업데이트
	m_vVelocity.x += totalAccel.x * dt;
	m_vVelocity.y += totalAccel.y * dt;
	m_vVelocity.z += totalAccel.z * dt;

	// 위치 업데이트
	auto transform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	if (transform)
	{
		glm::vec3 pos = transform->GetPosition();
		pos.x += m_vVelocity.x * dt;
		pos.y += m_vVelocity.y * dt;
		transform->SetPosition(pos);
	}

	// 매 프레임 힘, 가속도 초기화
	m_vForce = { 0.f, 0.f,0.f };
	m_vAccelation = { 0.f, 0.f,0.f };
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
		auto vel = iter_compData->find(VelocityName);
		m_vVelocity.x=  vel->begin().value();
		m_vVelocity.x = vel->begin().value()+1;

		auto acc = iter_compData->find(AccelatioinName);
		m_vAccelation.x = acc->begin().value();
		m_vAccelation.y = acc->begin().value()+1;
	}
}

json RigidBody::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = RigidBodyTypeName;

	json compData;
	compData[VelocityName] = { m_vVelocity.x,m_vVelocity.y };
	compData[AccelatioinName] = { m_vAccelation.x,m_vAccelation.y };
	data[CompDataName] = compData;

	return data;
}
