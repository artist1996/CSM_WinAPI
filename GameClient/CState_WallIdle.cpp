#include "pch.h"
#include "CState_WallIdle.h"
#include "CPlayerEffectMgr.h"

CState_WallIdle::CState_WallIdle()
{
}

CState_WallIdle::~CState_WallIdle()
{
}

void CState_WallIdle::Enter()
{
	Initialize();

	CPlayerEffectMgr::GetInst()->SetActive(false);

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"WALL_IDLE_RIGHT", true);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"WALL_IDLE_LEFT", true);
	}
}

void CState_WallIdle::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		if (KEY_PRESSED(KEY::LEFT))
		{
			vPos += Vec2(-1.f, 0.f) * 300.f * DT;
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetRigidBody()->SetWall(false);
			GetFSM()->ChangeState(L"FALL");
		}

		if (KEY_RELEASED(KEY::RIGHT))
		{
			vPos += Vec2(-1.f, 0.f) * 20.f;
			GetObj()->SetPos(vPos);
			GetRigidBody()->SetWall(false);
			GetFSM()->ChangeState(L"FALL");
		}
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		if (KEY_PRESSED(KEY::RIGHT))
		{
			//vPos += Vec2(1.f, 0.f) * 300.f * DT;
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetRigidBody()->SetWall(false);
			GetFSM()->ChangeState(L"FALL");
		}

		if (KEY_RELEASED(KEY::LEFT))
		{
			vPos += Vec2(1.f, 0.f) * 20.f;
			GetObj()->SetPos(vPos);
			GetRigidBody()->SetWall(false);
			GetFSM()->ChangeState(L"FALL");
		}
	}

	if (KEY_PRESSED(KEY::Z) && KEY_TAP(KEY::X))
	{
		GetObj()->SetSpeed(600.f);
		GetRigidBody()->SetWall(false);
		GetFSM()->ChangeState(L"WALLKICK");
		return;
	}

	if (KEY_NONE(KEY::Z) && KEY_TAP(KEY::X))
	{
		GetObj()->SetSpeed(250.f);
		GetRigidBody()->SetWall(false);
		GetFSM()->ChangeState(L"WALLKICK");
		return;
	}

	if (GetRigidBody()->IsGround())
	{
		GetRigidBody()->SetGround(true);
		GetRigidBody()->SetBlock(true);
		GetFSM()->ChangeState(L"LANDING");
		return;
	}
}

void CState_WallIdle::Exit()
{
}