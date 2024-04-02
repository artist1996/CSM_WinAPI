#include "pch.h"
#include "CState_Attack03.h"
#include "CPlayer.h"

CState_Attack03::CState_Attack03()
{
}

CState_Attack03::~CState_Attack03()
{
}

void CState_Attack03::Enter()
{
	Initialize();
	
	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"ATTACK03_RIGHT", false);
		static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK03);
	}

	if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"ATTACK03_LEFT", false);
		static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK03);
	}
}

void CState_Attack03::FinalTick()
{
	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CState_Attack03::Exit()
{
}