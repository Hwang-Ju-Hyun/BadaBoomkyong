#include "Transform.h"
#include "GameObject.h"
#include "Window.h"
#include "GameObjectManager.h"
#include "Serializer.h"


Transform::Transform(GameObject* _owner)
	:BaseComponent(_owner)
{
	SetName(this->TransformTypeName);
}

Transform::~Transform()
{
}

glm::mat3 Transform::GetModelToNDC_Matrix() const
{	
	return m_mModeltoNDC;
}

void Transform::Init(){}

void Transform::Update()
{
	float window_width  = static_cast<float>(Window::GetInstance()->GetWindowWidth());
	float window_height = static_cast<float>(Window::GetInstance()->GetWindowHeight());
	
	glm::mat3 transform =
	{
		1,				0,				0,			//	1 0 position x	
		0,				1,				0,			//	0 1 position y
		m_vPosition.x,  m_vPosition.y,	1			//  0 0 1
	};
	glm::mat3 scale =
	{
		m_vScale.x,0,0,								// scale 0 0
		0,m_vScale.y,0,								// 0 scale 0
		0,0,1										// 0  0    1
	};
	glm::mat3 rotation =						
	{
		std::cos(m_fRotation),	std::sin(m_fRotation),0,				//cos() -sin() 0
		-std::sin(m_fRotation),	std::cos(m_fRotation),0,				//sin() cos()  0
		0,						0,					  1					// 0      0    1
	};
	glm::mat3 WorldtoNDC =
	{
		1.f/window_width,		0,				0,
		0,					1.f/window_height,	0,
		0,						0,				1
	};

	m_mModeltoWorld = (transform  * rotation * scale);
	m_mModeltoNDC = WorldtoNDC*m_mModeltoWorld;
}
 
void Transform::Exit()
{

}

BaseRTTI* Transform::CreateTransformComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();	
	BaseRTTI* comp = last_obj->AddComponent_and_Get(TransformTypeName, new Transform(last_obj));	
	if(comp!=nullptr)
		return comp;
	return nullptr;
}

void Transform::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto pos = iter_compData->find(PositionName);
		m_vPosition.x = pos->begin().value();
		m_vPosition.y = (pos->begin()+1).value();
		m_vPosition.z = (pos->begin() + 2).value();

		auto sca = iter_compData->find(ScaleName);
		m_vScale.x = sca->begin().value();
		m_vScale.y = (sca->begin()+1).value();

		auto rot= iter_compData->find(RotationName);
		m_fRotation = rot->begin().value();
	}
}

json Transform::SaveToJson(const json& _str)
{	
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = TransformTypeName;

	json compData;
	compData[PositionName] = { m_vPosition.x,m_vPosition.y,m_vPosition.z };
	compData[ScaleName] = { m_vScale.x,m_vScale.y };
	compData[RotationName] = { m_fRotation };

	data[CompDataName] = compData;
	
	return data;	
}
