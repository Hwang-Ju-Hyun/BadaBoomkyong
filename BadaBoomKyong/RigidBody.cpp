#include "RigidBody.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Serializer.h"
#include "TimeManager.h"

RigidBody::RigidBody(GameObject* _owner)
	:BaseComponent(_owner)
{
	SetName(this->RigidBodyTypeName);
}

RigidBody::~RigidBody()
{
}

void RigidBody::Init()
{

}

void RigidBody::Update()
{
	double dt = TimeManager::GetInstance()->GetDeltaTime();
	m_vVelocity.x = m_vVelocity.x + m_vAccelation.x * dt;
	m_vVelocity.y = m_vVelocity.y + m_vAccelation.y * dt;
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
