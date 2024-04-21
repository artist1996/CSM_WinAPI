#include "pch.h"
#include "CBoss_Idle.h"

#include "CLevelMgr.h"

#include "CAnimation.h"
#include "CHUD_Boss.h"
#include "CHUD_BossHP.h"


CBoss_Idle::CBoss_Idle()
	: m_Dir(-1.f)
	, m_Time(0.f)
	, m_bEncounter(true)
	, m_Attack(false)
	, m_bBreath(false)
	, m_Count(false)
	, m_Rand(0)
	, m_CurDir(0.f)
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
		CHUD_Boss* pHUD = new CHUD_Boss;
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, pHUD);
		CHUD_BossHP* pHP = new CHUD_BossHP;
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, pHP);
	}

	else if(!m_bEncounter)
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->Play(L"IDLE_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->Play(L"IDLE_LEFT", false);
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

	else if (vPos.x - pTarget->GetPos().x > 0.f)
	{
		m_Dir = -1.f;
		GetObj()->SetDirection(DIRECTION::LEFT);
	}

	if (1.f == m_Dir && m_CurDir != m_Dir)
	{
		GetAnimator()->Play(L"IDLE_RIGHT", false);
		GetObj()->SetDirection(DIRECTION::RIGHT);
	}
	
	else if (-1.f == m_Dir && m_CurDir != m_Dir)
	{
		GetAnimator()->Play(L"IDLE_LEFT", false);
		GetObj()->SetDirection(DIRECTION::LEFT);
	}

	if (!m_Count)
	{
		m_Time += DT;
	}

	if (1.f <= m_Time)
	{
		if (m_bBreath)
		{
			m_Rand = rand() % 3;
		}

		else
		{
			m_Rand = rand() % 4;
		}
		m_Time = 0.f;
		m_Attack = true;
		m_Count = true;
	}

	if (m_Attack)
	{
		switch (m_Rand)
		{
		case 0:
			// Hadouken
			m_bBreath = false;
			GetFSM()->ChangeState(L"HADOUKEN");
			break;
		case 1:
			// Soryugen
			m_bBreath = false;
			GetFSM()->ChangeState(L"SORYUGEN");
			break;
	
		case 2:
			// DiveKick
			m_bBreath = false;
			GetFSM()->ChangeState(L"DIVEKICK");
			break;
	
		case 3:
			// Breath
			m_bBreath = true;
			GetFSM()->ChangeState(L"BREATH");
			break;
		}
	}
}

void CBoss_Idle::Exit()
{
	m_Attack = false;
	m_bEncounter = false;
	m_Time = 0.f;
	m_Count = false;
}