#include "PositionOverLifeTime.h"
#include "ParticleSystem.h"

PositionOverLifeTime::PositionOverLifeTime(const glm::vec3& _start, const glm::vec3& _end)
	:m_vPosStart(_start)
	,m_vPosEnd(_end)
{
}

PositionOverLifeTime::~PositionOverLifeTime()
{
}

void PositionOverLifeTime::Update(Particle& _particle, float _dt)
{
    //gpt 코드임 꼭 공부하셈
    float t = 1.f - (_particle.m_fLifeRemaining / _particle.m_fLifeTime);

    if (t < 0.8f)
    {
        // ========================
        // 회오리 + 약간의 흔들림
        // ========================
        float spiralRadiusX = 50.f;
        float spiralRadiusZ = 30.f;
        float angle = t / 0.8f * 6.2831853071795864769 + _particle.m_fAngleOffset;

        glm::vec3 spiralOffset;
        spiralOffset.x = cos(angle) * spiralRadiusX;
        spiralOffset.z = sin(angle) * spiralRadiusZ;

        // 살짝 위아래 흔들림 추가
        spiralOffset.y = sin(angle * 3.f + _particle.m_fAngleOffset) * 5.f;

        // 랜덤 흔들림
        spiralOffset += _particle.m_vRandomDir * 5.f;

        _particle.m_vPosition = _particle.m_vPositionStart + spiralOffset;
    }
    else
    {
        // ========================
        // 중앙으로 흡수
        // ========================
        float easeT = (t - 0.8f) / 0.2f; // 0~1 정규화
        easeT = easeT * easeT;            // 가속(ease-in)

        // lerp를 원래 위치에서 End로
        _particle.m_vPosition = glm::mix(_particle.m_vPosition, _particle.m_vPositionEnd, easeT);
    }
}