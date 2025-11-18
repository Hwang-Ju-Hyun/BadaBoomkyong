#include "Melee.h"
#include "GameObjectManager.h"
#include "GameObject.h"

Melee::Melee(GameObject* _owner, GameObject* _attacker)
	:MonoBehaviour(_owner)
    ,m_pAttacker(_attacker)
    ,m_iDamage(1)
{
    GetOwner()->SetIsSerializable(false);
}

Melee::~Melee()
{
}

BaseRTTI* Melee::CreateMeleeComponent()
{
    GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
    BaseRTTI* comp = last_obj->AddComponent_and_Get(Melee::MeleeTypeName, new Melee(last_obj));
    if (comp != nullptr)
        return comp;
    return nullptr;
}
