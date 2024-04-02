#include "pch.h"
#include "CRaiden_Attack.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAnimation.h"
#include "CAttack_Raiden.h"


CRaiden_Attack::CRaiden_Attack()
{
}

CRaiden_Attack::~CRaiden_Attack()
{
}

void CRaiden_Attack::Enter()
{
	Initialize();

	GetAnimator()->Play(L"ATTACK", false);
	CAttack_Raiden* pAttack = new CAttack_Raiden(GetObj(), GetAnimator());
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_MISSILE, pAttack);
}

void CRaiden_Attack::FinalTick()
{
	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"STANDBY");
		return;
	}
}

void CRaiden_Attack::Exit()
{
}