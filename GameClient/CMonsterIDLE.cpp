#include "pch.h"
#include "CMonsterIDLE.h"

CMonsterIDLE::CMonsterIDLE()
{
}

CMonsterIDLE::~CMonsterIDLE()
{
}

void CMonsterIDLE::Enter()
{
}

void CMonsterIDLE::FinalTick()
{
	
	float Range = GetBlackboardData<float>(L"DetectRange");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");

	if (pPlayer->GetPos().GetDistance(pSelf->GetPos()) < Range)
		GetFSM()->ChangeState(L"Trace");
	
	DrawDebugCircle(PEN_TYPE::PEN_BLUE, pSelf->GetPos(), Vec2(Range * 2.f, Range * 2.f), 0.f);
}

void CMonsterIDLE::Exit()
{
}