#include "pch.h"
#include "CMettool_Idle.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CMettool_Idle::CMettool_Idle()
	: m_Time(0.f)
{
}

CMettool_Idle::~CMettool_Idle()
{
}

void CMettool_Idle::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"IDLE_RIGHT", true);
	}
	
	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"IDLE_LEFT", true);
	}
}

void CMettool_Idle::FinalTick()
{
	if (L"Editor" != CLevelMgr::GetInst()->GetCurrentLevel()->GetName())
	{
		m_Time += DT;
	}

	if (1.f <= m_Time)
	{
		GetFSM()->ChangeState(L"PATROL");
		return;
	}
}

void CMettool_Idle::Exit()
{
	m_Time = 0.f;
}