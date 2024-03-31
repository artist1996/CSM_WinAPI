#include "pch.h"
#include "CState_Fastfall.h"

CState_Fastfall::CState_Fastfall()
{
}

CState_Fastfall::~CState_Fastfall()
{
}

void CState_Fastfall::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"FASTFALL_RIGHT", true);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"FASTFALL_LEFT", true);
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
		GetObj()->SetDirection(DIRECTION::RIGHT);
		GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FASTFALL_RIGHT"));
	}

	else if (KEY_TAP(KEY::LEFT))
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FASTFALL_LEFT"));
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