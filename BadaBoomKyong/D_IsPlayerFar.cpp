#include "D_IsPlayerFar.h"
#include "Boss.h"
#include "BlackBoard.h"

D_IsPlayerFar::D_IsPlayerFar(BTNode* _child)
	:m_pChild(_child)
{
}

D_IsPlayerFar::~D_IsPlayerFar()
{
}

BTNodeState D_IsPlayerFar::Enter(BlackBoard& _bb)
{
	return BTNodeState::RUNNING;
}

BTNodeState D_IsPlayerFar::Update(BlackBoard& _bb)
{
    // ���� �Ǵ�
    Boss* boss = _bb.GetBoss();
    if (_bb.IsPlayerNearX(boss))
        return BTNodeState::FAILURE; // ���� �Ҹ��� �� FAIL

    // ���� ���� �� �ڽ� ����
    return m_pChild->Tick(_bb);
}

void D_IsPlayerFar::Exit(BlackBoard& _bb)
{
    // �ڽĵ� �ʿ��ϸ� Exit ȣ��
    m_pChild->Exit(_bb);
}

void D_IsPlayerFar::Abort()
{
    m_pChild->Abort();
}
