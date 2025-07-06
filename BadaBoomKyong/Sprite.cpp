#include "Sprite.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include <cassert>
#include "Serializer.h"
#include "BaseComponent.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Resource.h"

Sprite::Sprite(GameObject* _owner)
	:MonoBehaviour(_owner)
{
	SetName(SpriteTypeName);
}

Sprite::~Sprite()
{
}

void Sprite::Init()
{
}

void Sprite::Update()
{
}

void Sprite::Exit()
{
}

BaseRTTI* Sprite::CreateSpriteComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseComponent* p = last_obj->AddComponent_and_Get(SpriteTypeName, new Sprite(last_obj));
	if(p!=nullptr)
		return p;
	return nullptr;
}

void Sprite::LoadFromJson(const json& _str)
{
	auto comp_data=_str.find(CompDataName);
	if (comp_data != _str.end())
	{
		auto color = comp_data->find(ColorName);
		m_vColor.r = color->begin().value();
		m_vColor.g = (color->begin()+1).value();
		m_vColor.b = (color->begin()+2).value();
		m_vColor.a = (color->begin()+3).value();

		auto texture_name = comp_data->find(TextureTypeName);
		auto texture_path = comp_data->find(TexturePathTypeName);
		if (texture_name != comp_data ->end() && texture_path != comp_data->end())
		{		
			TextureResource* res= dynamic_cast<TextureResource*>(ResourceManager::GetInstance()->GetAndLoad(texture_name.value(), texture_path.value()));
			assert(res != nullptr);
			m_pTextureResource = res;
		}
	}
}

json Sprite::SaveToJson(const json& _str)
{
	json data;
	auto serial = Serializer::GetInstance();
	data[serial->ComponentTypeNameInJson] = SpriteTypeName;
	
	json compData;
	compData[ColorName] = { m_vColor.r,m_vColor.g,m_vColor.b,m_vColor.a };

	if (m_pTextureResource != nullptr)
	{
		compData[TextureTypeName] = { m_pTextureResource->GetResourceName() };
		compData[TexturePathTypeName] = { m_pTextureResource->GetResourcePath() };
	}
	
	data[CompDataName] = compData;
	return data;
}

#ifdef _DEBUG
void Sprite::EditInfoFromButton()
{	
	ImGui::InputFloat4("Color", &m_vColor[0]);
	ImGui::ColorEdit3("Color", (float*)&m_vColor);
}
#endif // DEBUG