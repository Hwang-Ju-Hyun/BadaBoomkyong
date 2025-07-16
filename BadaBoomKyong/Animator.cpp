#include "Animator.h"
#include "GameObject.h"
#include "GameObjectManager.h"

Animator::Animator(GameObject* _owner)
	:BaseComponent(_owner)
{
}

Animator::~Animator()
{
}

void Animator::Init()	
{
}

void Animator::Awake()
{
}

void Animator::Update()
{
}

void Animator::Exit()
{
}

void Animator::ChangeAnimation()
{
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
}

json Animator::SaveToJson(const json& _str)
{
	return json();
}
