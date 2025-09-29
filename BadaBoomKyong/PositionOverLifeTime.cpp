#include "PositionOverLifeTime.h"
#include "ParticleSystem.h"
PositionOverLifeTime::PositionOverLifeTime(PositionFuncPointer _func)
	:m_func(_func)
{
}

PositionOverLifeTime::~PositionOverLifeTime()
{
}

void PositionOverLifeTime::Update(Particle& _particle, float _progress, float _dt)
{    
    
    float t = 1.f - (_particle.m_fLifeRemaining / _particle.m_fLifeTime);    
    _particle.m_vPosition = m_func(_particle, t, _dt);
    //if (t < 0.8f)
    //{
    //    // ========================
    //    // ȸ���� + �ణ�� ��鸲
    //    // ========================
    //    float spiralRadiusX = 50.f;
    //    float spiralRadiusZ = 30.f;
    //    float angle = t / 0.8f * 6.2831853071795864769 + _particle.m_fAngleOffset;

    //    glm::vec3 spiralOffset;
    //    spiralOffset.x = cos(angle) * spiralRadiusX;
    //    spiralOffset.z = sin(angle) * spiralRadiusZ;

    //    // ��¦ ���Ʒ� ��鸲 �߰�
    //    spiralOffset.y = sin(angle * 3.f + _particle.m_fAngleOffset) * 5.f;

    //    // ���� ��鸲
    //    spiralOffset += _particle.m_vRandomDir * 5.f;

    //    _particle.m_vPosition = _particle.m_vPositionStart + spiralOffset;
    //}
    //else
    //{
    //    // ========================
    //    // �߾����� ���
    //    // ========================
    //    float easeT = (t - 0.8f) / 0.2f; // 0~1 ����ȭ
    //    easeT = easeT * easeT;            // ����(ease-in)

    //    // lerp�� ���� ��ġ���� End��
    //    _particle.m_vPosition = glm::mix(_particle.m_vPosition, _particle.m_vPositionEnd, easeT);
    //}
}