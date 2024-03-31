#include "pch.h"
#include "CState_Landing.h"

CState_Landing::CState_Landing()
{
}

CState_Landing::~CState_Landing()
{
}

void CState_Landing::Enter()
{
	Initialize();
	
	GetRigidBody()->SetWall(false);

	GetCollider()->SetScale(Vec2(90.f, 105.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"LANDING_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"LANDING_LEFT", false);
	}
}

void CState_Landing::FinalTick()
{
	if (GetAnimator()->GetCurAnim()->IsFinish() && GetRigidBody()->IsBlock())
	{
		GetFSM()->ChangeState(L"BLOCK");
		return;
	}


	if (GetAnimator()->GetCurAnim()->IsFinish() && !GetRigidBody()->IsBlock())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CState_Landing::Exit()
{
}