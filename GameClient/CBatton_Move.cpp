#include "pch.h"
#include "CBatton_Move.h"

CBatton_Move::CBatton_Move()
{
}

CBatton_Move::~CBatton_Move()
{
}

void CBatton_Move::Enter()
{
	Initialize();
	
	GetAnimator()->Play(L"IDLE", true);
}

void CBatton_Move::FinalTick()
{
	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");
	Vec2 vPos = GetObj()->GetPos();

	if (abs(vPos.x - pTarget->GetPos().x) < 30.f)
	{
		GetFSM()->ChangeState(L"ATTACK");
		return;
	}

	if (abs(vPos.x - pTarget->GetPos().x) > 1000.f)
	{
		GetObj()->Destroy();
		return;
	}

	vPos += Vec2(-1.f, 0.f) * 100.f * DT;
	GetObj()->SetPos(vPos);
	
	
}

void CBatton_Move::Exit()
{
}