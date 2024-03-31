#include "pch.h"
#include "CState_Fall.h"

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

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"FALL_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"FALL_LEFT", false);
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
		GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FALL_RIGHT"));
		GetObj()->SetDirection(DIRECTION::RIGHT);
	}

	else if (KEY_TAP(KEY::LEFT))
	{
		GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"FALL_LEFT"));
		GetObj()->SetDirection(DIRECTION::LEFT);
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