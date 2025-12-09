#include "Player.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "Serializer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Camera.h"
#include <cassert>
#include "GeometryUtill.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "FactoryManager.h"
#include "EventManager.h"
#include "Pistol.h"
#include "MeleeFactory.h"
#include "Melee.h"
#include "PlayerMelee.h"
#include "Animator.h"
#include "Anim_IdleState.h"
#include "Anim_HurtState.h"
#include "Anim_NormalAttackState_2.h"
#include "Anim_NormalAttackState_3.h"
#include "Anim_HolySlash.h"
#include <functional>
#include "HolySlashParticle.h"
#include "ParticleSystem.h"
#include "CollisionManager.h"
#include "GameStateManager.h"
#include "BaseLevel.h"
#include "Stage02.h"
#include "RenderManager.h"
#include "UIManager.h"
#include "UICanvas.h"
#include "UIWidget.h"
#include "UIPanel.h"
#include "AudioManager.h"
#include "MathUtil.h"

class AnimIdelState;
template<typename T>
class AnimFallState;


Player::Player(GameObject* _owner)
	:MonoBehaviour(_owner)		
{
	SetName(PlayerTypeName);
	m_pTransform = dynamic_cast<Transform*>(GetOwner()->FindComponent(Transform::TransformTypeName));	
	m_pSprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
	m_pRigidBody= dynamic_cast<RigidBody*>(GetOwner()->FindComponent(RigidBody::RigidBodyTypeName));
	m_pCollider = dynamic_cast<Collider*>(GetOwner()->FindComponent(Collider::ColliderTypeName));	
	assert(m_pTransform && m_pSprite && m_pCollider&&m_pRigidBody);			

	m_pAnimator = dynamic_cast<Animator*>(GetOwner()->FindComponent(Animator::AnimatorTypeName));

	m_pAnimStateMachine = new AnimStateMachine<Player>(this);	
	
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::IDLE),     new AnimIdleState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::TOSPRINT), new AnimToSprintState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::SPRINTING),new AnimSprintingState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::DASH),     new AnimDashState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::JUMP), new AnimJumpState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::FALL), new AnimFallState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::COMBO_ATTACK_1), new AnimNormalAttackState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::COMBO_ATTACK_2), new AnimNormalAttackState_2<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::COMBO_ATTACK_3), new AnimNormalAttackState_3<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::RUN_ATTACK), new AnimSprintAttackState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::JUMP_ATTACK), new AnimJumpAttackState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::HURT), new AnimHurtState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::DEATH), new AnimDeathState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::LAND), new AnimLandState<Player>());
	m_pAnimStateMachine->RegisterAnimState(int(PlayerAnimState::HOLY_SLASH), new AnimHolySlash<Player>());
	m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::IDLE);
	
	m_pPs = new ParticleSystem;
	m_pHolySlashParticle = new HolySlashParticle(m_pPs,this->GetOwner());	

	

	//todo 바인드 이거 ㅈ나게 ㅈ같음 그리고 AddComboIndex했을때 반환이 int가 사실아님! 씨발! Chatgpt CollisionManager 코드 분석 맨끝줄에 설명있음
	//todo 이거 지금은 주석되어있는데 중요한 문법들 많아서 시간있을때 참고해서 공부해보셈
	//AnimationSpriteSheet* anim_clip = m_pAnimator->GetSpriteSheet("ComboAtk_1");
	//anim_clip->m_vecAnimEvent.push_back({ 9, std::bind(&Player::AddComboIndex,this) });
	//anim_clip->m_vecAnimEvent.push_back({ 15,std::bind(&Player::AddComboIndex,this) });
	//anim_clip->m_vecAnimEvent.push_back({ 24,std::bind(&Player::AddComboIndex,this) });	
}

Player::~Player()
{
	if (m_pAnimStateMachine)
	{
		delete m_pAnimStateMachine;
		m_pAnimStateMachine = nullptr;
	}				
}

void Player::Init()
{			
	m_pBulletFactory = dynamic_cast<BulletFactory*>(FactoryManager::GetInstance()->GetFactory(BulletFactory::BulletFactoryTypeName));
	m_pMeleeFactory = dynamic_cast<MeleeFactory*>(FactoryManager::GetInstance()->GetFactory(MeleeFactory::MeleeFactoryTypeName));
	assert(m_pBulletFactory != nullptr && m_pMeleeFactory != nullptr);

	AudioManager::GetInstance()->LoadSound("jump", "../Extern/Assets/Sound/jump.mp3", false);
	AudioManager::GetInstance()->LoadSound("dash", "../Extern/Assets/Sound/dash.wav", false);
	AudioManager::GetInstance()->LoadSound("combo1", "../Extern/Assets/Sound/combo1.wav", false);
	AudioManager::GetInstance()->LoadSound("combo2", "../Extern/Assets/Sound/combo2.wav", false);
	AudioManager::GetInstance()->LoadSound("combo3", "../Extern/Assets/Sound/combo3.mp3", false);
	AudioManager::GetInstance()->LoadSound("jumpAttack", "../Extern/Assets/Sound/jumpAttack.flac", false);
	AudioManager::GetInstance()->LoadSound("playerHurt", "../Extern/Assets/Sound/playerHurt.mp3", false);	
	AudioManager::GetInstance()->LoadSound("playerDeath", "../Extern/Assets/Sound/playerDeath.wav", false);
}

void Player::Awake()
{	
	m_fCurrentHP = m_fInitHP;
	m_bIsAlive = true;
	m_pCam = RenderManager::GetInstance()->GetCamera();
	InitHPBarUi();
	InitDashBarUI();
}

void Player::Exit()
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
	if (m_pHolySlashParticle)
		delete m_pHolySlashParticle;
	if (m_pPs)
		delete m_pPs;
}

void Player::Update() 
{				
	auto input = InputManager::GetInstance();	
	m_ePreviousState = m_eCurrentState;	
	//todo : 이거 dashable & isalive이런거 함수화 시켜서 movable로 고치든가하자
	m_vPosition = m_pTransform->GetPosition();	

	if (m_bIsAlive&&!m_bIsDashing)
	{
		if (!m_bIsHurting)
		{
			Move();
			Jump();
			Fire();
			MeleeAttack();
			HolySlash();
			ComboUpdate();
		}
	}	


	if (GetDamageTaken() > 0)
	{
		float dam_taken = GetDamageTaken();
		float cur_hp = GetCurrentHP();
		float ratio = float(dam_taken) / float(cur_hp);
		float new_width = ratio * m_pHPPanelUI->GetScale().x;
		m_pHPPanelUI->SetWidth(m_pHPPanelUI->GetScale().x - new_width);
		m_fCurrentHP -= dam_taken;
		m_bIsHurting = true;
		SetDamageTaken(0);
	}

	HPMPBarUpdate();
	Dash();
	Death();
	
	StateHandler();	

	if (m_pAnimStateMachine)
		m_pAnimStateMachine->Update();			
}

void Player::EnterCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
		jumpPressed = false;			
	}	
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::DEATH_ZONE)
	{
		std::cout << "Enter : lava col" << std::endl;
		m_fCurrentHP = 0;
	}
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PORTAL)
	{
		if (GameStateManager::GetInstance()->GetCurrentLevel()->GetStageType() == STAGE_TYPE::STAGE_01)
		{			
			BaseLevel* lvl_2 = GameStateManager::GetInstance()->FindLevel(STAGE_TYPE::STAGE_02);
			EventManager::GetInstance()->LevelChange(lvl_2);
		}
		if (GameStateManager::GetInstance()->GetCurrentLevel()->GetStageType() == STAGE_TYPE::STAGE_02)
		{
			BaseLevel* lvl_3 = GameStateManager::GetInstance()->FindLevel(STAGE_TYPE::STAGE_TEST);
			EventManager::GetInstance()->LevelChange(lvl_3);
		}
	}		
}

void Player::OnCollision(Collider* _other)
{		
	if (_other->GetOwner()->GetGroupType() == GROUP_TYPE::PLATFORM)
	{
		GeometryUtil::GetInstance()->HandlePosition_CollisionAABB(_other->GetOwner(), this->GetOwner());
	}	
}

void Player::ExitCollision(Collider* _other)
{	
	if (m_pRigidBody->GetIsGround())
	{
		m_pRigidBody->SetIsGround(false);				
	}		
}

void Player::Move() 
{	
	auto input = InputManager::GetInstance();
	glm::vec3 velocity = m_pRigidBody->GetVelocity();
	velocity.x = 0.f;	
	if (input->GetKetCode(GLFW_KEY_X) == GLFW_REPEAT)
	{
		if (m_iDir == -1)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
			if (sprite)
				sprite->SetIsFlipX(false); // 왼x쪽 볼 때 FlipX 켜기
			m_iDir *= -1;
		}
		velocity.x = m_fSpeed;
	}
	if (input->GetKetCode(GLFW_KEY_Z) == GLFW_REPEAT)
	{		
		if (m_iDir == 1)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(GetOwner()->FindComponent(Sprite::SpriteTypeName));
			if (sprite)
				sprite->SetIsFlipX(true); // 왼쪽 볼 때 FlipX 켜기
			m_iDir *= -1;
		}		
		velocity.x = -m_fSpeed; 
	}
	
	m_pRigidBody->SetVelocity(velocity);
	std::fabs(velocity.x) > 0 ? m_bIsMoving = true:m_bIsMoving=false;
	

	glm::vec3 dir = glm::normalize(glm::vec3{ 0.1f,-1.f,0.f });
	m_ray = { m_pCollider->GetFinalPosition(),dir };
	if (CollisionManager::GetInstance()->RayCast(m_ray, m_pCollider->GetScale().y-15.f, m_rayHit, GROUP_TYPE::PLATFORM))
	{		
		m_pRigidBody->SetIsGround(true);
	}
	else
	{
		m_pRigidBody->SetIsGround(false);
	}
	
}

void Player::Fire()
{
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_J) == GLFW_PRESS)
	{
		Bullet* bullet_comp = m_pBulletFactory->CreateBullet(BULLET_TYPE::PISTOL);
		m_pBullet = bullet_comp;		

		EventManager::GetInstance()->SetActiveTrue(m_pBullet->GetOwner());
	}	
}

void Player::MeleeAttack()
{
	auto input = InputManager::GetInstance();
	m_pMelee = m_pMeleeFactory->CreateMelee(GROUP_TYPE::PLAYER);	
	if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{								
		
		PlayerMelee* melee_comp = dynamic_cast<PlayerMelee*>(m_pMelee);
		assert(melee_comp != nullptr);

		if (std::fabs(m_pRigidBody->GetVelocity().x) > 0 && std::fabs(m_pRigidBody->GetVelocity().y) <= g_epsilon)
			m_bSprintMeleeAttacking = true;
		else if (std::fabs(m_pRigidBody->GetVelocity().y) > 0 &&
			m_pAnimator->GetAnimation()->m_bLoopCount < 1)
			m_bJumpMeleeAttacking = true;
		else
			m_bNormalMeleeAttacking = true;		
		
		if (!m_bJumpMeleeAttacking)
		{
			//콤보 로직 <- 근데 이거 다시 짜보자 공부 좀 하고...
			if (!m_bInNormalCombo) // 밀리어택 중이 아닐때
			{
				StartComboStep(ComboStep::COMBO_1);     // 1타 시작				
			}
			else //밀리어택중이었는데 또 입력이 들어오면
			{
				m_bComboQueue = true;               // 다음 단계 예약(즉시 전환 X)		
			}
		}			
	}		
	if (m_pAnimator->GetAnimation()->m_sAnimationName == "ComboAtk_3")
	{
		if (m_pAnimator->GetCurrentFrameIndex() == 4)
		{
			m_bCanMeleeAttack = true;
			EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
			//m_pMelee->GetOwner()->SetActive(true);
			//m_pMelee->GetOwner()->CallAwakeAllComp();
		}
	}
	else
	{
		if ((m_bJumpMeleeAttacking||m_bInNormalCombo)&&m_pAnimator->GetCurrentFrameIndex()==2)
		{
			m_bCanMeleeAttack = true;
			//std::cout << m_pAnimator->GetAnimation()->m_sAnimationName << std::endl;
			//m_pMelee->GetOwner()->SetActive(true);
			EventManager::GetInstance()->SetActiveTrue(m_pMelee->GetOwner());
			//m_pMelee->GetOwner()->CallAwakeAllComp();
		}		
	}
	if ((m_bJumpMeleeAttacking || m_bInNormalCombo) && m_pAnimator->GetCurrentFrameIndex() == m_pAnimator->GetAnimation()->m_iSheet_Max - 3)
	{
		//m_pMelee->GetOwner()->SetActive(false);
		EventManager::GetInstance()->SetActiveFalse(m_pMelee->GetOwner());
	}
	
}

void Player::Dash()
{
	m_pDashPanelUI->SetPos(m_vPosition.x-40.f, m_vPosition.y+55.f, m_vPosition.z);
	auto input = InputManager::GetInstance();
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	
	if (input->GetKetCode(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{					
		m_bIsDashInput = true;
	}
	if (m_fDashCoolTime >= 2.99f && m_bDashable&&m_bIsDashInput)
	{
		m_fDashAccTime += dt;		
		if (m_fDashAccTime <= m_fDashDuration)
		{
			m_pDashPanelUI->AddWidth((m_fDash_bar_width / m_fDashDuration) * dt * -1);			
			m_bIsDashing = true;
			m_pRigidBody->SetVelocity({ m_iDir * m_fDashSpeed,0.f,0.f });
		}
		else
		{
			if (m_pDashPanelUI->GetScale().x <= 10.f)
			{
				m_pDashPanelUI->SetWidth(0.f);				
			}			
			m_pDashPanelUI->SetWidth(0.f);
			m_bDashable = false;
			m_bIsDashInput = false;
			m_fDashCoolTime = 3.f;
			m_fDashAccTime = 0.f;
		}
	}
	if (m_bDashable == false)
	{
		m_bIsDashing = false;
		m_bIsDashInput = false;
		m_fDashCoolTime -= dt;
		m_pDashPanelUI->AddWidth(dt * (m_fDash_bar_width / 3.f));//3.f==DashCoolTime
		if (m_fDashCoolTime <= 0.01f)
		{
			m_pDashPanelUI->SetWidth(m_fDash_bar_width);
			m_fDashCoolTime =3.f;
			m_bDashable = true;
		}
	}	
}

void Player::Death()   
{		
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_fCurrentHP = 0;

	m_fCurrentHP > 0 ? m_bIsAlive = true : m_bIsAlive=false;

	if (!m_bIsAlive)
	{
		m_bIsHurting = false;		
		m_eCurrentState = PlayerAnimState::DEATH;		
	}
}

float Player::m_fComboAccTime = 0.f;
void Player::ComboUpdate()
{		
	float dt = TimeManager::GetInstance()->GetDeltaTime();			

	// === 기본 콤보 진행 ===
	if (!m_bInNormalCombo) return;

	if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
	{
		// 바로 다음 단계로 진행하거나 종료
		if (m_bComboQueue && m_eComboStep != ComboStep::COMBO_3)
		{
			AdvanceCombo();
			return;
		}
		EndCombo();
	}
}

void Player::HPMPBarUpdate()
{
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	auto a = m_pHPPanelUI->GetWidth();

	if (m_pHPPanelUI->GetWidth() < 730.f)
	{
		m_fHPBarFill_Elapse += dt;		
	}
	if (m_fHPBarFill_MaxTime < m_fHPBarFill_Elapse)
		m_bSholudFill_HP = true;

	float hp_speed = 100.f;
	if (m_bSholudFill_HP)
	{
		if (m_pHPPanelUI->GetWidth() + dt * hp_speed > 730.f)
		{
			m_pHPPanelUI->SetWidth(730.f);
			m_bSholudFill_HP = false;
			m_fHPBarFill_Elapse = 0.f;
		}			
		m_pHPPanelUI->AddWidth(dt * 100.f);
		if (m_bIsHurting)
		{
			m_bSholudFill_HP = false;
			m_fHPBarFill_Elapse = 0.f;
		}
		m_fCurrentHP = MathUtil::GetInstance()->clamp(m_fCurrentHP + (5.f / m_pHPPanelUI->GetWidth()), 0.f,m_fInitHP);
	}

	if (m_pMPPanelUI->GetWidth() < 439.f)
	{
		m_fMPBarFill_Elapse += dt;
	}
	if (m_fMPBarFill_MaxTime < m_fMPBarFill_Elapse)
		m_bSholudFill_MP = true;

	float mp_speed = 100.f;
	if (m_bSholudFill_MP)
	{
		if (m_pMPPanelUI->GetWidth() + dt * mp_speed > 439.f)
		{
			m_pMPPanelUI->SetWidth(439.f);
			m_bSholudFill_MP = false;
			m_fMPBarFill_Elapse = 0.f;
		}
		m_pMPPanelUI->AddWidth(dt * mp_speed);
		m_fCurrentMP = MathUtil::GetInstance()->clamp(m_fCurrentMP + (3.f / m_pMPPanelUI->GetWidth()), 0.f, m_fInitMP);
	}	
}

void Player::StateHandler()
{
	if (m_eCurrentState == PlayerAnimState::DEATH)
		return;
	if (m_bIsSprinting)
		std::fabs(m_pRigidBody->GetVelocity().x) <= g_epsilon ? m_bIsSprinting = false : m_bIsSprinting = true;

	m_pRigidBody->GetVelocity().y < 0 ? m_bIsFalling = true : m_bIsFalling = false;

	if (m_bIsHurting == false)
	{
		if (m_pRigidBody->GetIsGround() && std::fabs(m_pRigidBody->GetVelocity().x) > g_epsilon
			&& (!m_bSprintMeleeAttacking && !m_bIsDashing))
		{						
			m_eCurrentState = PlayerAnimState::TOSPRINT;						
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_bIsSprinting = true;					
				m_eCurrentState = PlayerAnimState::SPRINTING;				
			}			
		}		
		if (m_bIsFalling)
		{
			m_eCurrentState = PlayerAnimState::FALL;		
		}
		

		if (m_bJumpMeleeAttacking)
		{
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
				m_bJumpMeleeAttacking = false;
			else
			{
				m_eCurrentState = PlayerAnimState::JUMP_ATTACK;				
			}									
		}

		
		if (m_bInNormalCombo)
		{
			switch (m_eComboStep)
			{
			case ComboStep::COMBO_1:   m_eCurrentState = PlayerAnimState::COMBO_ATTACK_1; break;
			case ComboStep::COMBO_2:   m_eCurrentState = PlayerAnimState::COMBO_ATTACK_2; break;
			case ComboStep::COMBO_3: m_eCurrentState = PlayerAnimState::COMBO_ATTACK_3; break;
			default:
				break;
			}
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
				m_bNormalMeleeAttacking = false;
				m_pMelee->SetIsMeleeAttacking(false);
			}
			else if(m_pAnimator->GetCurrentFrameIndex()>=2)
			{
				m_pMelee->SetIsMeleeAttacking(true);

			}
			return; // 다른 상태로 덮어쓰지 않게 조기 리턴			
		}

		if (std::fabs(m_pRigidBody->GetVelocity().x) <= g_epsilon && (m_pRigidBody->GetVelocity().y <= g_epsilon
			&& m_pRigidBody->GetIsGround())&&!m_bHolySlashing)
		{
			m_bJumpMeleeAttacking = false;
			m_eCurrentState = PlayerAnimState::IDLE;			
		}						
		

		if (m_bHolySlashing)
		{
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;;
				m_bHolySlashing = false;
			}
		}

		if (m_bIsDashing)
		{
			m_eCurrentState = PlayerAnimState::DASH;
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
				m_bIsDashing= false;
			}
		}			
		if (m_bSprintMeleeAttacking)
		{
			m_eCurrentState = PlayerAnimState::RUN_ATTACK;
			if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pAnimator->GetAnimation()->m_bLoopCount = 0;
				m_bSprintMeleeAttacking = false;
			}
		}
	}
	

	if (m_bIsHurting&&m_bIsAlive)
	{
		m_pTransform->AddPositionX(-m_iDir * 1.0f);
		m_eCurrentState = PlayerAnimState::HURT;	
	}
			
	if (m_bIsHurting)
	{
		if (m_pAnimator->GetAnimation()->m_bLoopCount >= 1)
		{
			m_pAnimator->GetAnimation()->m_bLoopCount = 0;
			m_bIsHurting = false;
		}
	}	
}

void Player::Jump()
{
	auto input = InputManager::GetInstance();
	if (input->GetKetCode(GLFW_KEY_SPACE) == GLFW_PRESS && m_pRigidBody->GetIsGround())
	{
		m_iCurJumpCount++;
		jumpPressed = true;		
		glm::vec3 velocity = m_pRigidBody->GetVelocity();
		velocity.y = m_fJumpImpulse;
		m_pRigidBody->SetVelocity(velocity);
		m_pRigidBody->SetIsGround(false);
		m_eCurrentState = PlayerAnimState::JUMP;

		
		AudioManager::GetInstance()->PlaySound("jump", 0.7f);
	}
}

const char* Player::GetComboClipName(ComboStep _step) const
{
	switch (_step)
	{
	case ComboStep::COMBO_1:   return "ComboAtk_1";
	case ComboStep::COMBO_2:   return "ComboAtk_2";
	case ComboStep::COMBO_3: return "ComboAtk_3";
	default:               return nullptr;
	}
}

void Player::StartComboStep(ComboStep step)
{
	if (step == ComboStep::NONE) 
		return;

	m_eComboStep = step;
	m_bInNormalCombo = true;
	m_bCanMeleeAttack = true;     // 이동 잠깐 묶고(기존 Move() 가 이 값으로 체크)
	m_bComboQueue = false;
	m_fComboAccTime = 0.0f;	

	//EventManager::GetInstance()->SetActiveFalse(m_pMelee->GetOwner());

	//애니메이션 강제전환
	switch (step)
	{
	case ComboStep::COMBO_1:	
		m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_1);
		break;
	case ComboStep::COMBO_2:
	{						
		m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_2);
		break;
	}		
	case ComboStep::COMBO_3:
	{
		m_bCanMeleeAttack = true;
		m_pMelee->SetDamage(2);
		m_pAnimStateMachine->ChangeAnimState(PlayerAnimState::COMBO_ATTACK_3);				
		break;
	}		
	default: 
		break;
	}
}

void Player::AdvanceCombo()
{
	if (!m_bInNormalCombo) 
		return;
	
	if (m_eComboStep == ComboStep::COMBO_1)
	{	
		StartComboStep(ComboStep::COMBO_2);
	}		
	else if (m_eComboStep == ComboStep::COMBO_2)
		StartComboStep(ComboStep::COMBO_3);
	else  
		EndCombo(); // 이미 마지막이면 종료
	
}

void Player::EndCombo()
{

	m_bInNormalCombo = false;
	m_bComboQueue = false;
	m_eComboStep = ComboStep::NONE;
	m_iComboIndex = 0;
	m_bCanMeleeAttack = false; // 이동 다시 허용
	m_eCurrentState = PlayerAnimState::IDLE;
}
static int a = 0;

void Player::HolySlash()
{ 	
	if (!m_pRigidBody->GetIsGround())
		return;
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	auto input = InputManager::GetInstance();	
	if (input->GetKetCode(GLFW_KEY_Q) == GLFW_PRESS)
	{		
		m_eCurrentState = PlayerAnimState::HOLY_SLASH;
		m_bHolySlashing = true;
		m_pHolySlashParticle->CreateParticles(m_pHolySlashParticle->GetEmitSize());		
	}	
	if (m_bHolySlashing)
	{		
		if (m_bIsHurting)
		{
			m_bShouldZoomOut = true;
		}
		else if (m_pAnimator->GetAnimation()->m_sAnimationName=="HolySlash" 
			&& m_pAnimator->GetCurrentFrameIndex() == 20
			&& m_bHolySlashFlag == false)
		{
			Bullet* bullet_comp = m_pBulletFactory->CreateBullet(BULLET_TYPE::PISTOL);
			m_pBullet = bullet_comp;
			assert(m_pBullet != nullptr);
			EventManager::GetInstance()->SetActiveTrue(m_pBullet->GetOwner());			
			m_bHolySlashFlag = true;
			m_bShouldZoomOut = true;			


			float mp_taken = 1.f; //1==mp taken
			float cur_mp = GetCurrentMP();
			float ratio = float(1.f) / float(cur_mp);
			float new_width = ratio * m_pMPPanelUI->GetScale().x;
			m_pMPPanelUI->SetWidth(m_pMPPanelUI->GetScale().x - new_width);
			m_fCurrentMP -= 1;		

		}
		else if (m_pAnimator->GetCurrentFrameIndex() == 20 && m_bHolySlashFlag == true)
		{
			m_bHolySlashFlag = true;
		}
		else
		{
			m_bHolySlashFlag = false;
		}		
	
		float zoom_in_speed = 250.f;
	
		
		if (m_bHolySlashing && m_pAnimator->GetCurrentFrameIndex() < 20&&m_pAnimator->GetAnimation()->m_sAnimationName == "HolySlash")
		{
			m_pCam->AddCamPosOffset({ 0.f,0.f,-dt * zoom_in_speed });			
		}					
	}

	if (m_bShouldZoomOut)
	{
		float zoom_out_speed = 1600.f;
		m_pCam->AddCamPosOffset({ 0.f,0.f,dt * zoom_out_speed });
		if (m_pCam->GetCamPosOffset().z > m_pCam->GetCamPosOriginOffset().z)
		{
			m_pCam->SetCamPosOffset(m_pCam->GetCamPosOriginOffset());
			m_bShouldZoomOut = false;
			m_bHolySlashing = false;
		}
	}
	
}

void Player::InitHPBarUi()
{
	glm::vec3 pos = m_pTransform->GetPosition();
	glm::vec3 scale = m_pTransform->GetScale();

	m_pHPCanvasUI = new UICanvas(UIRenderSpace::SCREEN_SPACE);
	UIWidget* HP_Bar_Widget = new UIWidget(m_pHPCanvasUI);

	m_pPanelBorderUI = new UIPanel(HP_Bar_Widget->GetOwner(),10.f,200.f, 0.f, 870.f, 170.f);
	TextureResource* hp_border_tex = m_pPanelBorderUI->LoadTexture("HP_Bar_Border", "../Extern/Assets/Texture/UI/PlayerHP_UI/base.png");
	m_pPanelBorderUI->SetPivot({ 0.f,0.f });

	m_pHPPanelUI = new UIPanel(HP_Bar_Widget->GetOwner(), 117.f, 122.f, 0.f, 730.f, 36.f);
	m_pHPPanelUI->SetPivot({ 0.0f, 0.0f });	
	m_pHPPanelUI->SetColor(glm::vec4{ 1.0f,0.f,0.f,1.f });

	m_pMPPanelUI = new UIPanel(HP_Bar_Widget->GetOwner(), 131.f, 152.f, 0.f, 439.f, 17.f);
	m_pMPPanelUI->SetPivot({ 0.0f, 0.0f });
	m_pMPPanelUI->SetColor(glm::vec4{ 0.0f,0.f,1.f,1.f });

	HP_Bar_Widget->AddChild(m_pHPPanelUI);
	HP_Bar_Widget->AddChild(m_pMPPanelUI);
	HP_Bar_Widget->AddChild(m_pPanelBorderUI);


	m_pHPCanvasUI->AddChild(HP_Bar_Widget);	

	m_pHPCanvasUI->Init();

	//m_pHPPanelUI->m_fpMouseOn = []() {GameObjectManager::GetInstance()->GameRestart();};

	UIManager::GetInstance()->AddCanvas(m_pHPCanvasUI);
}

void Player::InitDashBarUI()
{
	glm::vec3 pos = m_pTransform->GetPosition();
	glm::vec3 scale = m_pTransform->GetScale();

	m_pDashCanvasUI = new UICanvas(UIRenderSpace::WORLD_SPACE);
	UIWidget* Dash_Bar_Widget = new UIWidget(m_pDashCanvasUI);	

	m_pDashPanelUI= new UIPanel(Dash_Bar_Widget->GetOwner(), pos.x-60.f,pos.y+80.f,pos.z, m_fDash_bar_width, 10.f);
	m_pDashPanelUI->SetPivot({ 0.f,0.f });
	//TextureResource* tx = m_pDashPanelUI->LoadTexture("HP_Bar", "../Extern/Assets/Texture/UI/Health_Bars/Style_1.png");

	m_pDashCanvasUI->Init();
	m_pDashPanelUI->SetColor(glm::vec4{ 1.0f,0.f,1.f,1.f });
	Dash_Bar_Widget->AddChild(m_pDashPanelUI);
	m_pDashCanvasUI->AddChild(Dash_Bar_Widget);


	UIManager::GetInstance()->AddCanvas(m_pDashCanvasUI);
}


bool Player::GetIsJumping() const
{
	return m_pRigidBody->GetVelocity().y >= 20;
}

BaseRTTI* Player::CreatePlayerComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(PlayerTypeName, new Player(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void Player::LoadFromJson(const json& _str)
{
	auto iter_compData = _str.find(CompDataName);
	if (iter_compData != _str.end())
	{
		auto speed = iter_compData->find(SpeedName);
		m_fSpeed = speed->begin().value();

		auto jump = iter_compData->find(JumpForceName);
		m_fJumpImpulse = jump->begin().value();		
	}
}

json Player::SaveToJson(const json& _str)
{
	json data;

	auto serializer = Serializer::GetInstance();
	data[serializer->ComponentTypeNameInJson] = PlayerTypeName;

	json compData;
	compData[SpeedName] = m_fSpeed;
	compData[JumpForceName] = m_fJumpImpulse;

	data[CompDataName] = compData;

	return data;
}