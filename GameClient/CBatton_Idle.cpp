#include "pch.h"
#include "CBatton_Idle.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster_Batton.h"
#include "CAttack_BattonBomb.h"


CBatton_Idle::CBatton_Idle()
	: m_Time(0.f)
	, m_Move(false)
{
}

CBatton_Idle::~CBatton_Idle()
{
}

void CBatton_Idle::Enter()
{
	Initialize();

	GetAnimator()->Play(L"IDLE", true);
	dynamic_cast<CMonster_Batton*>(GetObj())->SetBomb(true);
}

void CBatton_Idle::FinalTick()
{
	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");

	Vec2 vPos = GetObj()->GetPos();

	if (vPos.GetDistance(pTarget->GetPos()) < 300.f)
	{
		m_Move = true;
	}

	if (m_Move)
	{
		m_Time += DT;
	}

	if (0.1f < m_Time)
	{
		GetFSM()->ChangeState(L"MOVE");
		return;
	}
}

void CBatton_Idle::Exit()
{
	m_Time = 0.f;
	m_Move = false;
}