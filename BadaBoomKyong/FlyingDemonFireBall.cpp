#include "FlyingDemonFireBall.h"
#include "Gameobject.h"

FlyingDemonFireBall::FlyingDemonFireBall(GameObject* _owner, GameObject* _shooter)
	:Bullet(_owner, _shooter)
{
	GetOwner()->SetIsSerializable(false);
}

FlyingDemonFireBall::~FlyingDemonFireBall()
{
}

void FlyingDemonFireBall::Init()
{
}

void FlyingDemonFireBall::Awake()
{
}

void FlyingDemonFireBall::Update()
{
}

void FlyingDemonFireBall::Exit()
{
}

void FlyingDemonFireBall::EnterCollision(Collider* _col)
{
}

void FlyingDemonFireBall::OnCollision(Collider* _col)
{
}

void FlyingDemonFireBall::ExitCollision(Collider* _col)
{
}

void FlyingDemonFireBall::Fire()
{
}

void FlyingDemonFireBall::LoadFromJson(const json& _str)
{
}

json FlyingDemonFireBall::SaveToJson(const json& _str)
{
	return json();
}

BaseRTTI* FlyingDemonFireBall::CreateFireBallComponent()
{
	return nullptr;
}
