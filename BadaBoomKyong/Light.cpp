#include "Light.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Serializer.h"
#include "IMGUI/imgui.h"

Light::Light(GameObject* _owner)
    :MonoBehaviour(_owner)
{
	SetName(LightTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite    = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
}

Light::~Light()
{
}

void Light::Init()
{
}

void Light::Awake()
{
}

void Light::Update()
{
}

void Light::Exit()
{
}

BaseRTTI* Light::CreateLightComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(LightTypeName, new Light(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void Light::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{		
		auto light_type = iter_compData->find(LightType_TypeName);
		m_eType = light_type->begin().value();
		
		auto direction = iter_compData->find(DirectionTypeName);
		m_vDirection.x = direction->begin().value();
		m_vDirection.y = (direction->begin()+1).value();
		m_vDirection.z = (direction->begin() + 2).value();
		auto ambient = iter_compData->find(AmbientTypeName);
		m_vAmbient.x = ambient->begin().value();
		m_vAmbient.y = (ambient->begin()+1).value();
		m_vAmbient.z = (ambient->begin()+2).value();
		auto diffuse = iter_compData->find(DiffuseTypeName);
		m_vDiffuse.x = diffuse->begin().value();
		m_vDiffuse.y = (diffuse->begin()+1).value();
		m_vDiffuse.z = (diffuse->begin() + 2).value();
		auto specular = iter_compData->find(SpecularTypeName);
		m_vSpecular.x = specular->begin().value();
		m_vSpecular.y = (specular->begin()+1).value();
		m_vSpecular.z = (specular->begin()+2).value();		

		auto cutoff = iter_compData->find(CutoffAngleTypeName);
		m_fCutoffAngle = cutoff->begin().value();
	}
}

json Light::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = LightTypeName;

	json compData;
	compData[LightType_TypeName] = m_eType;
	compData[DirectionTypeName] = {m_vDirection.x,m_vDirection.y,m_vDirection.z};
	compData[AmbientTypeName] = { m_vAmbient.x,m_vAmbient.y,m_vAmbient.z };
	compData[DiffuseTypeName] = { m_vDiffuse.x,m_vDiffuse.y,m_vDiffuse.z };
	compData[SpecularTypeName] = { m_vSpecular.x,m_vSpecular.y,m_vSpecular.z };	
	compData[CutoffAngleTypeName] = { m_fCutoffAngle };
	data[CompDataName] = compData;

	return data;
}

#ifdef _DEBUG
void Light::EditInfoFromButton()
{	
	// LightType 선택용 문자열 배열
	const char* lightTypes[] = { "Point", "Directional", "Spot" };
	int currentType = static_cast<int>(m_eType);

	if (ImGui::Combo("Light Type", &currentType, lightTypes, IM_ARRAYSIZE(lightTypes)))
	{
		m_eType = static_cast<LightType>(currentType);
	}

	// 색상/강도 값 입력
	ImGui::InputFloat3("Ambient", &(m_vAmbient[0]));
	ImGui::InputFloat3("Diffuse", &(m_vDiffuse[0]));
	ImGui::InputFloat3("Specular", &(m_vSpecular[0]));

	// Spot light일 때만 Cutoff Angle 표시
	if (m_eType == LightType::SPOT_LIGHT)
	{
		ImGui::InputFloat("Cutoff Angle", &m_fCutoffAngle);
	}
}
#endif