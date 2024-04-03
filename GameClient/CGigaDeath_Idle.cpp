#include "pch.h"
#include "CGigaDeath_Idle.h"

CGigaDeath_Idle::CGigaDeath_Idle()
	: m_Time(2.f)
	, m_Attack(false)
{
}

CGigaDeath_Idle::~CGigaDeath_Idle()
{
}

void CGigaDeath_Idle::Enter()
{
}

void CGigaDeath_Idle::FinalTick()
{
	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");
	Vec2 vPos = GetObj()->GetPos();
	
	if (m_Attack)
	{
		m_Time += DT;
	}
	if (vPos.GetDistance(pTarget->GetPos()) < 600.f)
	{
		m_Attack = true;
	}

	if (2.f <= m_Time)
	{
		GetFSM()->ChangeState(L"ATTACK");
		return;
	}
}

void CGigaDeath_Idle::Exit()
{
	m_Attack = false;
	m_Time = 0.f;
}