#include "Monster.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Serializer.h"
#include "GeometryUtill.h"
#include "Collider.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"
#include "Player.h"
#include "MathUtil.h"
#include "FactoryManager.h"
#include "BulletFactory.h"

Monster::Monster(GameObject* _owner)
	:MonoBehaviour(_owner)
{		
	//Component Get
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pRigidBody = dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));
	GameObject* player_obj = GameObjectManager::GetInstance()->FindObject(Player::PlayerTypeName);
	m_pPlayer = dynamic_cast<Player*>(player_obj->FindComponent(Player::PlayerTypeName));
	m_pAI = dynamic_cast<AI*>(GetOwner()->FindComponent(AI::AITypeName));
	m_pAnimator = dynamic_cast<Animator*>(GetOwner()->FindComponent(Animator::AnimatorTypeName));
	assert(m_pTransform && m_pSprite && m_pRigidBody && m_pCollider && m_pPlayer&&m_pAI&&m_pAnimator);

	//Player Data Get
	m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
	m_vPlayerPosition = m_pPlayerTransform->GetPosition();
	assert(m_pPlayerTransform);
	
	//Basic Init 
	m_vPosition = m_pTransform->GetPosition();	
}

Monster::~Monster()
{
	if (m_pAnimStateMachine)
	{
		delete m_pAnimStateMachine;
		m_pAnimStateMachine = nullptr;
	}
	
}

void Monster::UpdateSpriteFlipX()
{
	if (m_fDirection < 0)//���� ����
	{
		if (m_pSprite)
			m_pSprite->SetIsFlipX(true); // ���� �� �� FlipX �ѱ�	
	}
	else//������ ����
	{
		if (m_pSprite)
			m_pSprite->SetIsFlipX(false);
	}
}

const std::string Monster::GetCurrentAnimState()
{

	switch (m_eCurrentState)
	{
	case MonsterAnimState::IDLE:
		return "Idle";		
	case MonsterAnimState::RANGE_ATTACK:
		return "RangeAttack";
	case MonsterAnimState::NORMAL_ATTACK:
		return "NormalAttack";
	case MonsterAnimState::WALK:
		return "Walk";
	case MonsterAnimState::HURT:
		return "Hurt";
	case MonsterAnimState::DIVE_START:
		return "DiveStart";
	case MonsterAnimState::TAKE_OFF:
		return "TakeOff";
	case MonsterAnimState::FLYING:
		return "Flying";
	case MonsterAnimState::DIVING:
		return "Flying";
	case MonsterAnimState::DEATH:
		return "Death";
	default:
		break;
	}
}
