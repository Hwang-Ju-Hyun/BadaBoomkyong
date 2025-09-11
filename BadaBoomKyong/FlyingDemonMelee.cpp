#include "FlyingDemonMelee.h"

FlyingDemonMelee::FlyingDemonMelee(GameObject* _owner, GameObject* _attacker)
    :Melee(_owner,_attacker)
{
}

FlyingDemonMelee::~FlyingDemonMelee()
{
}

void FlyingDemonMelee::Init()
{
}

void FlyingDemonMelee::Awake()
{
}

void FlyingDemonMelee::Update()
{
}

void FlyingDemonMelee::Exit()
{
}

void FlyingDemonMelee::EnterCollision(Collider* _col)
{
}

void FlyingDemonMelee::OnCollision(Collider* _col)
{
}

void FlyingDemonMelee::ExitCollision(Collider* _col)
{
}

void FlyingDemonMelee::LoadFromJson(const json& _str)
{
}

json FlyingDemonMelee::SaveToJson(const json& _str)
{
    return json();
}
