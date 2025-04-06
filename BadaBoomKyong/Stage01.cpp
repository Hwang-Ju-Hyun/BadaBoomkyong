#include "Stage01.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "Transform.h"

Stage01::Stage01(const std::string& _name)
	:BaseLevel(_name)
{
}

Stage01::~Stage01()
{
}

void Stage01::Init()
{
	const std::string tri_str = "tri";	
	tri = new GameObject(tri_str, MODEL_TYPE::TRIANGLE);
	tri->AddComponent(Transform::TypeName, new Transform(tri));
	Transform* trs = static_cast<Transform*>(tri->FindComponent(Transform::TypeName));	
	trs->SetScale({ 100.f,100.f,100.f });
	trs->SetPosition({ 10.f,10.f,0.f });

	const std::string rect_str = "rect";
	rec = new GameObject(rect_str, MODEL_TYPE::RECTANGLE);
	rec->AddComponent(Transform::TypeName, new Transform(rec));
	Transform* trs_rec = static_cast<Transform*>(rec->FindComponent(Transform::TypeName));
	trs_rec->SetScale({ 200.f,200.f,200.f });
	trs_rec->SetPosition({ 250.f,100.f,50.f });
}

void Stage01::Update()
{	
	
}

void Stage01::Exit()
{	
	GameObjectManager::GetInstance()->DeleteAllObject();
}
