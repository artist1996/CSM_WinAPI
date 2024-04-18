#include "pch.h"
#include "CState_Fastfall.h"

#include "CPlayerEffectMgr.h"

CState_Fastfall::CState_Fastfall()
{
}

CState_Fastfall::~CState_Fastfall()
{
}

void CState_Fastfall::Enter()
{
	Initialize();

	if (CPlayerEffectMgr::GetInst()->GetActive())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			CPlayerEffectMgr::GetInst()->Play(L"FALL_RIGHT", true);
		}
		
		else
		{
			CPlayerEffectMgr::GetInst()->Play(L"FALL_LEFT", true);
		}
	}

	if (GetObj()->IsBlack())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_FASTFALL_RIGHT", true);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_FASTFALL_LEFT", true);
		}
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"FASTFALL_RIGHT", true);
		}
	
		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"FASTFALL_LEFT", true);
		}
	}
}

void CState_Fastfall::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (GetRigidBody()->IsWall())
	{
		GetFSM()->ChangeState(L"WALL_ENTER");
		return;
	}

	if (KEY_TAP(KEY::C))
	{
		GetFSM()->ChangeState(L"RAKUOUHA");
		return;
	}

	if (KEY_TAP(KEY::RIGHT))
	{
		CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_RIGHT");
		if (GetObj()->IsBlack())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_FASTFALL_RIGHT"));
		}
		else
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FASTFALL_RIGHT"));
		}
	}

	else if (KEY_TAP(KEY::LEFT))
	{
		CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_LEFT");
		if(GetObj()->IsBlack())
		{ 
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_FASTFALL_LEFT"));
		}
		else
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FASTFALL_LEFT"));
		}
	}
	
	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos += Vec2(1.f, 0.f) * GetObj()->GetSpeed() * DT;
		GetObj()->SetPos(vPos);
	}

	else if (KEY_PRESSED(KEY::LEFT))
	{
		vPos += Vec2(-1.f, 0.f) * GetObj()->GetSpeed() * DT;
		GetObj()->SetPos(vPos);
	}

	if (KEY_TAP(KEY::C))
	{
		GetFSM()->ChangeState(L"RAKUOUHA");
		return;
	}

	if (GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"LANDING");
		return;
	}
}

void CState_Fastfall::Exit()
{
}