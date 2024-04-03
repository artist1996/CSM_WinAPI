#include "pch.h"
#include "CBatton_Attack.h"

#include "CAnimation.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster_Batton.h"
#include "CAttack_BattonBomb.h"

CBatton_Attack::CBatton_Attack()
{
}

CBatton_Attack::~CBatton_Attack()
{
}

void CBatton_Attack::Enter()
{
	Initialize();
	
	dynamic_cast<CMonster_Batton*>(GetObj())->SetBomb(false);

	CAttack_BattonBomb* pBomb = new CAttack_BattonBomb(GetObj(), false);
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_MISSILE, pBomb);
	

	GetAnimator()->Play(L"ATTACK", false);
}

void CBatton_Attack::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	vPos += Vec2(-1.f, 0.f) * 100.f * DT;
	GetObj()->SetPos(vPos);

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CBatton_Attack::Exit()
{
}