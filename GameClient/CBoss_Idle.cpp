#include "pch.h"
#include "CBoss_Idle.h"

#include "CAnimation.h"

CBoss_Idle::CBoss_Idle()
	: m_Dir(-1.f)
	, m_Time(0.f)
	, m_bEncounter(true)
	, m_Attack(false)
	, m_Rand(0)
{
}

CBoss_Idle::~CBoss_Idle()
{
}

void CBoss_Idle::Enter()
{
	Initialize();

	if (m_bEncounter)
	{
		GetAnimator()->Play(L"START", false);
		//m_bEncounter = false;
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->Play(L"IDLE_RIGHT", true);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->Play(L"IDLE_LEFT", true);
		}
	}
}

void CBoss_Idle::FinalTick()
{
	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");
	CObj* pTargetPlatform = GetBlackboardData<CObj*>(L"TargetPlatform");
	Vec2 vPos = GetObj()->GetPos();

	m_CurDir = m_Dir;

	if (vPos.x - pTarget->GetPos().x < 0.f)
	{
		m_Dir = 1.f;
		GetObj()->SetDirection(DIRECTION::RIGHT);
	}

	else if(vPos.x - pTarget->GetPos().x > 0.f)
	{
		m_Dir = -1.f;
		GetObj()->SetDirection(DIRECTION::LEFT);
	}

	if (1.f == m_Dir && m_CurDir != m_Dir)
	{
		GetAnimator()->Play(L"IDLE_RIGHT", true);
		GetObj()->SetDirection(DIRECTION::RIGHT);
	}

	else if (-1.f == m_Dir && m_CurDir != m_Dir)
	{
		GetAnimator()->Play(L"IDLE_LEFT", true);
		GetObj()->SetDirection(DIRECTION::LEFT);
	}

	if (m_bEncounter)
	{
		if (2 == GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			// HP Bar UI »ý¼º
			// m_bEncounter = false;
		}
	}

	m_Time += DT;
	
	if (1.f <= m_Time)
	{
		m_Rand = rand() % 4;
		m_Time = 0.f;
		m_Attack = true;
	}

	if (m_Attack)
	{
		GetFSM()->ChangeState(L"DIVEKICK");
	}
	//
	//if (m_Attack)
	//{
	//	switch (m_Rand)
	//	{
	//	case 0:
	//		// Hadouken
	//		GetFSM()->ChangeState(L"HADOUKEN");
	//		break;
	//	case 1:
	//		GetFSM()->ChangeState(L"SORYUGEN");
	//		// Soryugen
	//		break;
	//
	//	case 2:
	//		GetFSM()->ChangeState(L"DIVEKICK");
	//		// DiveKick
	//		break;
	//
	//	case 3:
	//		GetFSM()->ChangeState(L"BREATH");
	//		// Breath
	//		break;
	//	}
	//}
}

void CBoss_Idle::Exit()
{
	m_Attack = false;
	m_bEncounter = false;
	m_Time = 0.f;
}