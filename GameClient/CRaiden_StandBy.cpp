#include "pch.h"
#include "CRaiden_StandBy.h"

CRaiden_StandBy::CRaiden_StandBy()
	: m_Time(0.f)
{
}

CRaiden_StandBy::~CRaiden_StandBy()
{
}

void CRaiden_StandBy::Enter()
{
	Initialize();
	
	GetAnimator()->Play(L"IDLE", true);
}

void CRaiden_StandBy::FinalTick()
{
	m_Time += DT;

	if (1.f <= m_Time)
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CRaiden_StandBy::Exit()
{
	m_Time = 0.f;
}