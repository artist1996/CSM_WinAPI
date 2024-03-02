#include "pch.h"
#include "CMonsterTrace.h"

CMonsterTrace::CMonsterTrace()
{
}

CMonsterTrace::~CMonsterTrace()
{
}

void CMonsterTrace::Enter()
{
}

void CMonsterTrace::FinalTick()
{
	float Speed = GetBlackboardData<float>(L"Speed");
	CObj* pSelf = GetBlackboardData<CObj*>(L"Self");
	CObj* pPlayer = GetBlackboardData<CObj*>(L"Target");

	Vec2 vDir = pPlayer->GetPos() - pSelf->GetPos();

	vDir.Normalize();

	if (!vDir.IsZero())
	{
		Vec2 vPos = pSelf->GetPos() + (vDir * Speed * DT);
		pSelf->SetPos(vPos);
	}
}

void CMonsterTrace::Exit()
{
}
