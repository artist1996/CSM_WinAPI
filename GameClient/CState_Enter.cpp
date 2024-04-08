#include "pch.h"
#include "CState_Enter.h"

#include "CShadowMgr.h"

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
	CShadowMgr::GetInst()->Init();
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