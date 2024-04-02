#include "pch.h"
#include "CMettool_Patrol.h"

CMettool_Patrol::CMettool_Patrol()
	: m_Dir(1.f)
	, m_Speed(100.f)
	, m_ShootTime(0.f)
	, m_Attack(false)
{
}

CMettool_Patrol::~CMettool_Patrol()
{
}

void CMettool_Patrol::Enter()
{
	Initialize();

	if (-1.f == m_Dir)
	{
		GetAnimator()->Play(L"PATROL_LEFT", true);
	}
	
	else if (1.f == m_Dir)
	{
		GetAnimator()->Play(L"PATROL_RIGHT", true);
	}
}

void CMettool_Patrol::FinalTick()
{
	CObj* pTarget = GetFSM()->GetBlackboardData<CObj*>(L"Target");
	Vec2 vPos = GetObj()->GetPos();
	Vec2 vCenterPos = GetFSM()->GetBlackboardData<Vec2>(L"CenterPos");
	float DetectRange = GetFSM()->GetBlackboardData<float>(L"DetectRange");
	float MaxDistance = GetFSM()->GetBlackboardData<float>(L"MaxDistance");
	float Speed = GetFSM()->GetBlackboardData<float>(L"Speed");

	float fDist = abs(vCenterPos.x - vPos.x) - MaxDistance;
	
	if (vPos.GetDistance(pTarget->GetPos()) < 200.f)
	{
		m_ShootTime += DT;
	}

	if (m_ShootTime >= 1.f)
	{
		m_ShootTime = 0.f;
		m_Attack = true;
	}

	if (m_Attack)
	{
		GetFSM()->ChangeState(L"ATTACK");
		return;
	}

	vPos.x += m_Dir * m_Speed * DT;
	GetObj()->SetPos(vPos);
	
	if (1.f < fDist)
	{
		m_Dir *= -1.f;
		vPos.x += fDist * m_Dir;
		GetObj()->SetPos(vPos);
		if (m_Dir == -1.f)
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->Play(L"PATROL_LEFT", true);
		}
		
		else if (m_Dir == 1.f)
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->Play(L"PATROL_RIGHT", true);
		}
	}
}

void CMettool_Patrol::Exit()
{
	m_Attack = false;
}