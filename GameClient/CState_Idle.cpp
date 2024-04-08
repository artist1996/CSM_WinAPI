#include "pch.h"
#include "CState_Idle.h"

#include "CShadowMgr.h"

CState_Idle::CState_Idle()
{
}

CState_Idle::~CState_Idle()
{
}

void CState_Idle::Enter()
{
	Initialize();
	GetObj()->SetSpeed(300.f);
	GetCollider()->SetScale(Vec2(70.f, 105.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"IDLE_RIGHT", true);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"IDLE_LEFT", true);
	}
}

void CState_Idle::FinalTick()
{
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

	if (KEY_PRESSED(KEY::RIGHT) && KEY_PRESSED(KEY::LEFT))
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		return;
	}

	if (KEY_PRESSED(KEY::LEFT) && KEY_PRESSED(KEY::RIGHT))
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		return;
	}
	
	if (KEY_PRESSED(KEY::RIGHT))
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		GetFSM()->ChangeState(L"MOVE");
		return;
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		GetFSM()->ChangeState(L"MOVE");
		return;
	}

	if (KEY_PRESSED(KEY::Z) && KEY_TAP(KEY::X))
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			CShadowMgr::GetInst()->Play(L"JUMP_RIGHT", true);
			CShadowMgr::GetInst()->SetActive(true);
		}
		else
		{
			CShadowMgr::GetInst()->Play(L"JUMP_LEFT", true);
			CShadowMgr::GetInst()->SetActive(true);
		}
		GetObj()->SetSpeed(500.f);
		GetFSM()->ChangeState(L"JUMP");
		return;
	}

	if (KEY_TAP(KEY::Z))
	{
		GetObj()->SetSpeed(500.f);

		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetFSM()->ChangeState(L"DASH");
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetFSM()->ChangeState(L"DASH");
		}
		return;
	}

	if (KEY_TAP(KEY::X))
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetFSM()->ChangeState(L"JUMP");
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetFSM()->ChangeState(L"JUMP");
		}
		return;
	}

	if (KEY_TAP(KEY::C))
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetFSM()->ChangeState(L"ATTACK01");
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetFSM()->ChangeState(L"ATTACK01");
		}
		return;
	}
}

void CState_Idle::Exit()
{
}