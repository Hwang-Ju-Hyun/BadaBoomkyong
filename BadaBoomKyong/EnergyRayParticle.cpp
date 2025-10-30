#include "EnergyRayParticle.h"
#include "Boss.h"
#include "Transform.h"
#include "ParticleSystem.h"
#include "BossRange.h"
#include "RigidBody.h"
#include "MathUtil.h"

EnergyRayParticle::EnergyRayParticle(ParticleSystem* _ps, GameObject* _owner)
	:m_pParticleSystem(_ps),
    m_iParticle_PoolSize(200)
    ,m_fLifeTime(0.2f)
    ,m_SizeOverLifeTime(Decrease_Size)
{
    m_pParticleSystem->Init();    
    _ps->SetParticlePoolSize(m_iParticle_PoolSize);
	m_pBossRange = dynamic_cast<BossRange*>(_owner->FindComponent<Boss>());    
    m_pBossRangeRig= dynamic_cast<RigidBody*>(_owner->FindComponent<RigidBody>());
}

EnergyRayParticle::~EnergyRayParticle()
{
}

void EnergyRayParticle::CreateParticles(int _emitNum, glm::vec3 _start, glm::vec3 _end)
{
    glm::vec3 dir = _end - _start;
    float length = glm::length(dir);
    dir = glm::normalize(dir);

    float dirX{ _end.x - _start.x }; 
    float lengthX=std::fabs(_end.x)+std::fabs(_start.x);
    dirX < 0 ? dirX = -1 : dirX = 1;
    int beam_center = _emitNum-1;
    int beam_side = 1;
    
    IParticleBehavior* behavior[1] = { &m_SizeOverLifeTime };

    for (int i = 0; i < beam_center; i++)
    {
        float t = (float)i / (beam_center - 1);
        float posX = (_start.x + dirX*t * lengthX);              

        Particle p;
        p.m_vPosition = { (_start.x + _end.x) / 2,_start.y,0.f };
        p.m_vVelocity = glm::vec3(0);
        p.m_fLifeTime = m_fLifeTime;
        p.m_fLifeRemaining = p.m_fLifeTime;
        

        // 밝기가 일정하게 유지되도록
        p.m_vColor = glm::vec4(0.2f, 0.6f, 1.0f, 1.0f);        
        p.m_vSizeStart = { lengthX,30.f };
        p.m_vSize = { lengthX,30.f };
        p.m_vSizeEnd = { lengthX,0.f };
        m_pParticleSystem->Emit(p, behavior, 1);
    }

    Particle p_side;
    p_side.m_vPosition = { (_start.x + _end.x)/2,_start.y,0.f };
    p_side.m_vVelocity = glm::vec3(0);
    p_side.m_fLifeTime = m_fLifeTime;
    p_side.m_fLifeRemaining = p_side.m_fLifeTime;
    p_side.m_vColor = glm::vec4(0.2f, 0.6f, 1.0f, 1.0f);
    
    p_side.m_vSize={ lengthX,50.f };
    p_side.m_vSize.x = lengthX;
    p_side.m_vSize.y = 50.f;    


    p_side.m_vSizeStart = { lengthX,50.f };
    p_side.m_vSizeEnd = { lengthX,0.f };

    m_pParticleSystem->Emit(p_side, behavior, 1);
    m_pParticleSystem->SetRenderBillboard(false);
}

glm::vec2 EnergyRayParticle::Decrease_Size(Particle& _particle, float _progress, float _dt)
{        
    float t = MathUtil::GetInstance()->lerp(0.f, 1.f, _progress);

    _particle.m_vSize = { glm::mix(_particle.m_vSizeStart.x, _particle.m_vSizeEnd.x, t),glm::mix(_particle.m_vSizeStart.y, _particle.m_vSizeEnd.y, t) };
    return _particle.m_vSize;
}