#include "pch.h"
#include "CState_Fall.h"

#include "CPlayerEffectMgr.h"

CState_Fall::CState_Fall()
{
}

CState_Fall::~CState_Fall()
{
}

void CState_Fall::Enter()
{
	Initialize();


	GetCollider()->SetScale(Vec2(90.f, 130.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -65.f));

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
			GetAnimator()->Play(L"BLACK_FALL_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_FALL_LEFT", false);
		}
		return;
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"FALL_RIGHT", false);
		}
	
		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"FALL_LEFT", false);
		}
	}
}

void CState_Fall::FinalTick()
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
		if (GetObj()->IsBlack())
		{
			CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_RIGHT");
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_FALL_RIGHT"));
			GetObj()->SetDirection(DIRECTION::RIGHT);
		}

		else
		{
			CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_RIGHT");
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FALL_RIGHT"));
			GetObj()->SetDirection(DIRECTION::RIGHT);
		}
	}

	else if (KEY_TAP(KEY::LEFT))
	{
		if (GetObj()->IsBlack())
		{
			CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_LEFT");
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_FALL_LEFT"));
			GetObj()->SetDirection(DIRECTION::LEFT);
		}

		else
		{
			CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_LEFT");
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FALL_LEFT"));
			GetObj()->SetDirection(DIRECTION::LEFT);
		}
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		if (GetObj()->IsBlack())
		{
			CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_RIGHT");
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_FALL_RIGHT"));
			GetObj()->SetDirection(DIRECTION::RIGHT);
		}
		vPos += Vec2(1.f, 0.f) * GetObj()->GetSpeed() * DT;
		GetObj()->SetPos(vPos);
	}

	else if (KEY_PRESSED(KEY::LEFT))
	{
		if (GetObj()->IsBlack())
		{
			CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"FALL_LEFT");
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_FALL_LEFT"));
			GetObj()->SetDirection(DIRECTION::LEFT);
		}
		vPos += Vec2(-1.f, 0.f) * GetObj()->GetSpeed() * DT;
		GetObj()->SetPos(vPos);
	}

	if (GetAnimator()->GetCurAnim()->IsFinish() && !GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"FASTFALL");
		return;
	}
	
	if (GetRigidBody()->IsGround())
	{
		GetRigidBody()->SetJump(true);
		GetFSM()->ChangeState(L"LANDING");
		return;
	}
}

void CState_Fall::Exit()
{
}