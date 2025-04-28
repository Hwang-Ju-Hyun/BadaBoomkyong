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

Collider::Collider(GameObject* _owner)
	:BaseComponent(_owner),
	m_iID(g_iNextID)
{
	SetName(ColliderTypeName);

	m_pOwnerTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	assert(m_pOwnerTransform != nullptr);
	
	m_pColliderTransform= dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pColliderSpirte = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(m_pColliderTransform != nullptr && m_pColliderSpirte != nullptr);

	m_pModel = ModelManager::GetInstance()->FindModel(MODEL_TYPE::RECTANGLE);
	assert(m_pModel != nullptr);

	m_pColliderTransform->SetScale(m_vScale);
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

void Collider::OnCollision(Collider* _col)
{
	std::cout << "On Collision" << std::endl;
}

void Collider::CollisionEnter(Collider* _col)
{
	std::cout << "Enter Collision" << std::endl;
}

void Collider::CollisionExit(Collider* _col)
{
	std::cout << "Exit Collision" << std::endl;
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

#include "ComponentManager.h"
void Collider::DrawCollider()
{		
	auto shdr=RenderManager::GetInstance()->GetShader();
	auto shdr_handle = shdr->GetShaderProgramHandle();

	shdr->Use();	
	GLint Model_to_NDC_location = glGetUniformLocation(shdr_handle, "uModel_to_NDC");
	assert(Model_to_NDC_location >= 0);
	
	assert(m_pColliderTransform != nullptr);

	GLint ColorLocation = glGetUniformLocation(shdr_handle, "uColor");
	assert(ColorLocation >= 0);

	assert(m_pColliderSpirte != nullptr);

	glm::mat3 model_to_ndc = m_pColliderTransform->GetModelToNDC_Matrix();
	glm::vec4 color = m_pColliderSpirte->GetColor();
	color = { 0.f,1.f,0.f,1.f };
	glUniformMatrix3fv(Model_to_NDC_location, 1, GL_FALSE, glm::value_ptr(model_to_ndc));
	glUniform4fv(ColorLocation, 1, glm::value_ptr(color));

	m_pModel->Draw();shdr->Diuse();
}
