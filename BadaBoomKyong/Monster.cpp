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
#include "TimeManager.h"

#include "UICanvas.h"
#include "UIWidget.h"
#include "UIButton.h"
#include "UIManager.h"
#include "UIPanel.h"
#include "TextureResource.h"
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
	assert(m_pTransform && m_pSprite && m_pRigidBody && m_pCollider && m_pPlayer/*&&m_pAI*/&&m_pAnimator);

	//Player Data Get
	m_pPlayerTransform = dynamic_cast<Transform*>(m_pPlayer->GetOwner()->FindComponent(Transform::TransformTypeName));
	m_vPlayerPosition = m_pPlayerTransform->GetPosition();
	assert(m_pPlayerTransform);
	
	//Basic Init 
	m_vPosition = m_pTransform->GetPosition();	
}

Monster::~Monster()
{	
	if (m_pHPCanvasUI)
	{
		auto a = UIManager::GetInstance()->m_vecCanvases;
		UIManager::GetInstance()->RemoveCanvas(m_pHPCanvasUI);
		m_pHPCanvasUI = nullptr;
		auto b = UIManager::GetInstance()->m_vecCanvases;
	}
	if (m_pAnimStateMachine)
	{
		delete m_pAnimStateMachine;
		m_pAnimStateMachine = nullptr;
	}	
		
}

void Monster::UpdateSpriteFlipX()
{
	if (m_fDirection < 0)//왼쪽 볼때
	{
		if (m_pSprite)
			m_pSprite->SetIsFlipX(true); // 왼쪽 볼 때 FlipX 켜기	
	}
	else//오른쪽 볼때
	{
		if (m_pSprite)
			m_pSprite->SetIsFlipX(false);
	}
}

void Monster::Exit()
{
	
}

void Monster::OccurHitFlash()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	if (GetIsHurting())
	{
		m_fHitFlashAccTime += dt;
		if (m_fHitFlashDuration <= m_fHitFlashAccTime)
		{
			m_fHitFlashAccTime = 0.f;
			SetIsHurting(false);
		}
	}
	if (GetIsStagger())
	{
		if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
		{
			m_pAnimator->GetAnimation()->m_bLoopCount = 0;
			SetIsHurting(false);
			SetIsStagger(false);
		}
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

void Monster::InitHPBarUi()
{
	glm::vec3 pos = m_pTransform->GetPosition();
	glm::vec3 scale = m_pTransform->GetScale();

	m_pHPCanvasUI = new UICanvas(UIRenderSpace::WORLD_SPACE);
	UIWidget* HP_Bar_Widget = new UIWidget(m_pHPCanvasUI);
	
	m_pHPPanelBorderUI = new UIPanel(HP_Bar_Widget->GetOwner(), pos.x - 100.f, pos.y + 30.f, pos.z, 155.f, 10.f);
	TextureResource* hp_border_tex = m_pHPPanelBorderUI->LoadTexture("HP_Bar", "../Extern/Assets/Texture/UI/Health_Bars/Borders/Border_Style_4.png");
	m_pHPPanelBorderUI->SetPivot({ 0.f,0.f });
	
	m_pHPPanelUI = new UIPanel(HP_Bar_Widget->GetOwner(),0.f, 0.f, 1.f, 155.f, 10.f);
	m_pHPPanelUI->SetPivot({ 0.0f, 0.0f });
	TextureResource* hp_bar_tex = m_pHPPanelUI->LoadTexture("HP_Bar", "../Extern/Assets/Texture/UI/Health_Bars/Style_1.png");	

	m_pHPPanelBorderUI->AddChild(m_pHPPanelUI);

	m_pHPCanvasUI->Init();
	HP_Bar_Widget->AddChild(m_pHPPanelBorderUI);
	m_pHPCanvasUI->AddChild(HP_Bar_Widget);

	//m_pHPPanelUI->m_fpMouseOn = []() {GameObjectManager::GetInstance()->GameRestart();};

	UIManager::GetInstance()->AddCanvas(m_pHPCanvasUI);
} 

void Monster::HPBarUIUpdate()
{
	if (GetDamageTaken()<=0)
	{
		return;
	}	
}
