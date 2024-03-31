#include "pch.h"
#include "CState_Block.h"

CState_Block::CState_Block()
{
}

CState_Block::~CState_Block()
{
}

void CState_Block::Enter()
{
	Initialize();
	GetRigidBody()->SetWall(false);

	GetCollider()->SetScale(Vec2(90.f, 105.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -55.f));

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"IDLE_RIGHT", true);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"IDLE_LEFT", true);
	}
}

void CState_Block::FinalTick()
{
	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		if (KEY_TAP(KEY::RIGHT))
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			return;
		}

		else if (KEY_PRESSED(KEY::RIGHT))
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			return;
		}

		if (KEY_TAP(KEY::LEFT))
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetFSM()->ChangeState(L"MOVE");
			return;
		}
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		if (KEY_TAP(KEY::LEFT))
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			return;
		}

		else if (KEY_PRESSED(KEY::RIGHT))
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			return;
		}

		if (KEY_TAP(KEY::RIGHT))
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetFSM()->ChangeState(L"MOVE");
			return;
		}
	}
}

void CState_Block::Exit()
{
}