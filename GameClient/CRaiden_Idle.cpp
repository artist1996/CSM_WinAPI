#include "pch.h"
#include "CRaiden_Idle.h"
#include "CAnimation.h"

CRaiden_Idle::CRaiden_Idle()
{
}

CRaiden_Idle::~CRaiden_Idle()
{
}


void CRaiden_Idle::Enter()
{
	Initialize();

	GetAnimator()->Play(L"IDLE", true);
}

void CRaiden_Idle::FinalTick()
{
	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");
	float fDetectRange = GetBlackboardData<float>(L"DetectRange");

	if (GetObj()->GetPos().GetDistance(pTarget->GetPos()) < 200.f)
	{
		GetFSM()->ChangeState(L"ATTACK");
		return;
	}
}

void CRaiden_Idle::Exit()
{
}