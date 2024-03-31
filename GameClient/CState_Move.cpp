#include "pch.h"
#include "CState_Move.h"

CState_Move::CState_Move()
{
}

CState_Move::~CState_Move()
{
}

void CState_Move::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"WALK_RIGHT", true);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"WALK_LEFT", true);
	}
}

void CState_Move::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (!GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"FALL");
		return;
	}

	if (GetRigidBody()->IsWall() && GetRigidBody()->IsGround())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			if (KEY_TAP(KEY::RIGHT))
			{
				return;
			}

			else if (KEY_TAP(KEY::LEFT))
			{
				GetObj()->SetDirection(DIRECTION::LEFT);
				GetFSM()->ChangeState(L"MOVE");
			}
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			if (KEY_TAP(KEY::RIGHT))
			{
				GetObj()->SetDirection(DIRECTION::RIGHT);
				GetFSM()->ChangeState(L"MOVE");
			}

			else if (KEY_TAP(KEY::LEFT))
			{
				return;
			}
		}
	}

	if (KEY_TAP(KEY::Z))
	{
		GetObj()->SetSpeed(400.f);
		GetFSM()->ChangeState(L"DASH");
		return;
	}

	if (KEY_PRESSED(KEY::RIGHT) && KEY_PRESSED(KEY::LEFT)
		&& DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	if (KEY_PRESSED(KEY::LEFT) && KEY_PRESSED(KEY::RIGHT)
		&& DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		vPos += Vec2(1.f, 0.f) * GetObj()->GetSpeed() * DT;
		GetObj()->SetPos(vPos);
		return;
	}

	else if(KEY_RELEASED(KEY::RIGHT))
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		vPos += Vec2(-1.f, 0.f) * GetObj()->GetSpeed() * DT;
		GetObj()->SetPos(vPos);
		return;
	}

	else if (KEY_RELEASED(KEY::LEFT))
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CState_Move::Exit()
{
}