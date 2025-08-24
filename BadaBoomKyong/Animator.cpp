#include "Animator.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "TimeManager.h"
#include "Serializer.h"
#include "TextureResource.h"
#include "ResourceManager.h"
#include "Sprite.h"

Animator::Animator(GameObject* _owner)
	:BaseComponent(_owner)
{			
	SetName(AnimatorTypeName);	
}

Animator::~Animator()
{
	for (auto iter = m_mapAnimation.begin();iter != m_mapAnimation.end();iter++)
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}		
	}
	m_pCurrentAnimation = nullptr;
}
#include <iostream>

void Animator::Init()	
{				
	m_pCurrentAnimation = m_mapAnimation.find("Idle")->second;
	 //= new AnimationSpriteSheet(*original); // 복사	


	Sprite* spr = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));	
	spr->SetTexture(m_pCurrentAnimation->m_pTexture);
	if (m_pCurrentAnimation)
	{	
		m_pCurrentAnimation->m_fSheet_UV_Width = 1.f / m_pCurrentAnimation->m_iSheet_Col;
		m_pCurrentAnimation->m_fSheet_UV_Height = 1.f / m_pCurrentAnimation->m_iSheet_Row;
	}
	m_iCurrentFrameIndex = 0;

	int current_sheet_row = m_iCurrentFrameIndex / m_pCurrentAnimation->m_iSheet_Col;
	int current_sheet_col = m_iCurrentFrameIndex % m_pCurrentAnimation->m_iSheet_Col;

	m_pCurrentAnimation->m_fSheet_UV_offset_X = m_pCurrentAnimation->m_fSheet_UV_Width * current_sheet_col;
	m_pCurrentAnimation->m_fSheet_UV_offset_Y = m_pCurrentAnimation->m_fSheet_UV_Height * current_sheet_row;

	m_pCurrentAnimation->m_bLoopCount = 0;

	
}   

void Animator::Awake()
{
	m_pCurrentAnimation->m_bLoopCount = 0;
}
#include <iostream>
#include "CurseDemon.h"


void Animator::Update()
{
	if (!m_pCurrentAnimation)
	{
		std::cout << "Errror" << std::endl;
		return;
	}

	if (m_pCurrentAnimation->m_bLoop == false && m_pCurrentAnimation->m_bLoopCount >= 1)
	{
		m_pCurrentAnimation->m_bLoopCount = 0;
	}	
	
	float dt = TimeManager::GetInstance()->GetDeltaTime();
  	m_fAnmationAccTime += dt;	
		
	if (m_pCurrentAnimation->m_fDuration_per_frame <= m_fAnmationAccTime)
	{		   
		m_iCurrentFrameIndex += 1;
		m_iCurrentFrameIndex %= m_pCurrentAnimation->m_iSheet_Max;
		
		int current_sheet_row = m_iCurrentFrameIndex / m_pCurrentAnimation->m_iSheet_Col;
		int current_sheet_col = m_iCurrentFrameIndex % m_pCurrentAnimation->m_iSheet_Col;	

		m_pCurrentAnimation->m_fSheet_UV_offset_X = m_pCurrentAnimation->m_fSheet_UV_Width * current_sheet_col;
		m_pCurrentAnimation->m_fSheet_UV_offset_Y = m_pCurrentAnimation->m_fSheet_UV_Height * current_sheet_row;	
		m_fAnmationAccTime = 0.f;		
	}

	if (m_pCurrentAnimation->m_bLoop == false && m_iCurrentFrameIndex == m_pCurrentAnimation->m_iSheet_Max-1)
	{				
		m_pCurrentAnimation->m_bLoopCount++;
	}			
}

void Animator::Exit()
{	
}

AnimationSpriteSheet* Animator::AddSpriteSheet(std::string _name, AnimationSpriteSheet* _clip)
{
	m_mapAnimation.insert(std::make_pair(_name, _clip));
	return m_mapAnimation.find(_name)->second;
}

AnimationSpriteSheet* Animator::GetSpriteSheet(std::string _name)
{
	return m_mapAnimation.find(_name)->second;
}

void Animator::ChangeAnimation(const std::string& _animName)
{
	auto iter = m_mapAnimation.find(_animName);
	
	Sprite* spr = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	assert(spr != nullptr);

	m_pCurrentAnimation = iter->second;

	//// 깊은 복사된 새로운 시트를 만들고 현재 애니메이션으로 설정
	//AnimationSpriteSheet* cloned = new AnimationSpriteSheet(*iter->second);
	//m_pCurrentAnimation = cloned;	

	spr->SetTexture(iter->second->m_pTexture);
	
	if (m_pCurrentAnimation)
	{
		float sheet_uv_width, sheet_uv_height;
		sheet_uv_width = 1.f / m_pCurrentAnimation->m_iSheet_Col;
		sheet_uv_height = 1.f / m_pCurrentAnimation->m_iSheet_Row;	

		m_pCurrentAnimation->m_fSheet_UV_Width = sheet_uv_width;
		m_pCurrentAnimation->m_fSheet_UV_Height = sheet_uv_height;
	}

	m_iCurrentFrameIndex = 0; 
	int current_sheet_row = m_iCurrentFrameIndex / m_pCurrentAnimation->m_iSheet_Col;
	int current_sheet_col = m_iCurrentFrameIndex % m_pCurrentAnimation->m_iSheet_Col;

	m_pCurrentAnimation->m_fSheet_UV_offset_X = m_pCurrentAnimation->m_fSheet_UV_Width * current_sheet_col;
	m_pCurrentAnimation->m_fSheet_UV_offset_Y = m_pCurrentAnimation->m_fSheet_UV_Height * current_sheet_row;

	m_pCurrentAnimation->m_bLoopCount = 0;		
}

BaseRTTI* Animator::CreateAnimatiorComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(AnimatorTypeName, new Animator(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void Animator::LoadFromJson(const json& _str)
{
	auto comp_data = _str.find(CompDataName);	
	if (comp_data != _str.end())
	{
		auto animations = comp_data->find(AnimationsTypeName);
		if (animations != comp_data->end()
			&&animations->is_array())
		{
			for (const auto& animJson : *animations)
			{
				std::string name = animJson.value(AnimationNameTypeName, "Nothing");
				std::string texName = animJson.value(AnimationTextureNameTypeName, "Nothing");
				std::string texPath = animJson.value(AnimationTexturePathTypeName, "Nothing");
				int max = animJson.value(AnimationMaxTypeName, -1);
				int rows = animJson.value(AnimationRowTypeName, -1);
				int cols = animJson.value(AnimationColTypeName, -1);
				float duration = animJson.value(AnimationDurationTypeName, -0.1f);
				bool loop = animJson.value(AnimationLoopTypeName, false);
				
				TextureResource* res = dynamic_cast<TextureResource*>(ResourceManager::GetInstance()->GetAndLoad(texName,texPath));
				assert(res != nullptr);

				AnimationSpriteSheet* anim_sheet = new AnimationSpriteSheet;
				anim_sheet->m_sAnimationName = name;
				anim_sheet->m_pTexture = res;
				anim_sheet->m_iSheet_Max = max;
				anim_sheet->m_iSheet_Row = rows;
				anim_sheet->m_iSheet_Col = cols;
				anim_sheet->m_fDuration_per_frame = duration;
				anim_sheet->m_bLoop = loop;

				
				AddSpriteSheet(name, anim_sheet);
			}
		}
	}
}

json Animator::SaveToJson(const json& _str)
{
	json data;
	auto serial = Serializer::GetInstance();
	data[serial->ComponentTypeNameInJson] = AnimatorTypeName;

	json compData;
	compData[AnimationsTypeName] = json::array();

	for (auto iter = m_mapAnimation.begin();iter != m_mapAnimation.end();iter++)
	{		
		json animationEntry;
		animationEntry[AnimationNameTypeName] =     iter->second->m_sAnimationName;
		animationEntry[AnimationTextureNameTypeName] = iter->second->m_pTexture->GetResourceName();
		animationEntry[AnimationTexturePathTypeName] = iter->second->m_pTexture->GetResourcePath();
		animationEntry[AnimationMaxTypeName] = iter->second->m_iSheet_Max;
		animationEntry[AnimationRowTypeName] =      iter->second->m_iSheet_Row;
		animationEntry[AnimationColTypeName] =      iter->second->m_iSheet_Col;
		animationEntry[AnimationDurationTypeName] = iter->second->m_fDuration_per_frame;
		animationEntry[AnimationLoopTypeName] =     iter->second->m_bLoop;
		
		compData[AnimationsTypeName].push_back(animationEntry);
	}
	
	data[CompDataName] = compData;
	return data;
}


#ifdef _DEBUG
void Animator::EditInfoFromButton()
{
}
#endif // DEBUG