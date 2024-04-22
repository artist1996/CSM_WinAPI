#include "pch.h"
#include "CState_Enter.h"

#include "CPlayerEffectMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CHUD_Player.h"
#include "CHUD_PlayerHP.h"

CState_Enter::CState_Enter()
{
}

CState_Enter::~CState_Enter()
{
}

void CState_Enter::Enter()
{
	Initialize();

	GetAnimator()->Play(L"ENTER", false);
	CCamera::GetInst()->SetOwner(GetObj());

	CHUD_Player* pHUD = new CHUD_Player;
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, pHUD);

	CHUD_PlayerHP* pHP = new CHUD_PlayerHP;
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, pHP);

	GetObj()->SetHp(15);
}

void CState_Enter::FinalTick()
{
	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
	}
}

void CState_Enter::Exit()
{
	GetObj()->SetDirection(DIRECTION::RIGHT);
}