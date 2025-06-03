#include <GL/glew.h>
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObjectManager.h"
#include "Serializer.h"
#include "ModelManager.h"
#include "Model.h"
#include <iostream>
#include <cassert>
#include "Sprite.h"
#include <../GLM/gtc/type_ptr.hpp>	
#include "Shader.h"
#include "RenderManager.h"
#include "ICollisionHandler.h"

unsigned long long Collider::g_iNextID = 0;

Collider::Collider(GameObject* _owner)
	:MonoBehaviour(_owner),
	m_iID(g_iNextID++)
{
	SetName(ColliderTypeName);

	m_pOwnerTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	assert(m_pOwnerTransform != nullptr);
	
	m_pColliderTransform= dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pColliderSpirte = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pColliderTransform != nullptr && m_pColliderSpirte != nullptr);

	m_pColliderModel = ModelManager::GetInstance()->FindModel(MODEL_TYPE::RECTANGLE);
	assert(m_pColliderModel != nullptr);
}

Collider::~Collider()
{
}

void Collider::Init()
{	
}

void Collider::Update()
{
	glm::vec3 owner_pos=m_pOwnerTransform->GetPosition();
	m_vFinalPosition = owner_pos + m_vOffsetPosition;	
	m_pColliderTransform->SetPosition(m_vFinalPosition);
}

void Collider::Exit()
{
}

void Collider::SetColliderModelType(MODEL_TYPE _modelType)
{
	SetColModel(ModelManager::GetInstance()->FindModel(_modelType));
}

void Collider::EnterCollision(Collider* _col)
{
	NotifyCollisionToHandler(_col, &ICollisionHandler::EnterCollision);
}

void Collider::OnCollision(Collider* _col)
{
	NotifyCollisionToHandler(_col, &ICollisionHandler::OnCollision);
}

void Collider::ExitCollision(Collider* _col)
{
	NotifyCollisionToHandler(_col, &ICollisionHandler::ExitCollision);
}

//2번째 파라미터 
//멤버 함수 포인터 -> 공부는 했고 이해는 했는데 곧 까먹을듯 두고두고 시간있을때 보자 꽤나 유용하게 쓰일듯
void Collider::NotifyCollisionToHandler(Collider* _col, void(ICollisionHandler::*_ColFunc)(Collider*))
{
	std::unordered_map<std::string, BaseComponent*>  all_comp = _col->GetOwner()->GetAllComponentsOfObj_Hash();
	for (auto comp : all_comp)
	{
		if (comp.first == this->GetName())
			continue;
		ICollisionHandler* handler = dynamic_cast<ICollisionHandler*>(comp.second);		
		if (handler)
		{			
			//자기자신 호출
			(handler->*_ColFunc)(this);
		}
	}
}

BaseRTTI* Collider::CreateCollideComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(ColliderTypeName, new Collider(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void Collider::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto offset_pos = iter_compData->find(OffsetTypeName);
		m_vOffsetPosition.x = offset_pos->begin().value();
		m_vOffsetPosition.y = (offset_pos->begin() + 1).value();
		m_vOffsetPosition.z = (offset_pos->begin() + 2).value();

		auto sca = iter_compData->find(ScaleTypeName);
		m_vScale.x = sca->begin().value();
		m_vScale.y = (sca->begin() + 1).value();
		m_vScale.z = (sca->begin() + 2).value();		
	}
}

json Collider::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = ColliderTypeName;

	json compData;
	compData[OffsetTypeName] = {m_vOffsetPosition.x,m_vOffsetPosition.y,m_vOffsetPosition.z};
	compData[ScaleTypeName] = { m_vScale.x,m_vScale.y,m_vScale.z};

	data[CompDataName] = compData;

	return data;
}

#ifdef _DEBUG
#include "ComponentManager.h"
#include "RenderManager.h"
#include "Camera.h"
#include "Monster.h"
void Collider::DrawCollider()const
{

	auto shdr=RenderManager::GetInstance()->GetShader(SHADER_REF::THREE_DIMENSIONS);
	auto shadr_handle_3D = shdr->GetShaderProgramHandle();

	GLint IsColliderLocation = glGetUniformLocation(shadr_handle_3D, "uIsCollider");
	glUniform1i(IsColliderLocation, true); // true

	GLint DebugColorLocation = glGetUniformLocation(shadr_handle_3D, "uDebugColor");
	//assert(DebugColorLocation >= 0);
	
	Monster* mon = dynamic_cast<Monster*>(GetOwner()->FindComponent<Monster>());
	glm::vec4 color = { 0.f,1.f,0.f,1.f };
	mon->m_bCol == true ? color : color = { 1.0f,0.f,0.f,1.f };
	glUniform4fv(DebugColorLocation, 1, glm::value_ptr(color));

	m_pColliderModel->Draw();
	glUniform1i(IsColliderLocation, false);
	//shdr->Diuse();
}
#endif