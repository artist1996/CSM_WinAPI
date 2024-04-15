#include "pch.h"
#include "CState_WallEnter.h"

#include "CSound.h"

CState_WallEnter::CState_WallEnter()
	: m_pSound(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"WALL_ENTER", L"sound\\zero\\WALL_ENTER.wav");
}

CState_WallEnter::~CState_WallEnter()
{
}

void CState_WallEnter::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetCollider()->SetScale(Vec2(70.f, 115.f));
		GetCollider()->SetOffsetPos(Vec2(10.f, -55.f));
		GetAnimator()->Play(L"WALL_ENTER_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetCollider()->SetScale(Vec2(70.f, 115.f));
		GetCollider()->SetOffsetPos(Vec2(-10.f, -55.f));
		GetAnimator()->Play(L"WALL_ENTER_LEFT", false);
	}

	m_pSound->Play();
}

void CState_WallEnter::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (!GetRigidBody()->IsWall())
	{
		GetFSM()->ChangeState(L"FALL");
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
	}

	if (KEY_RELEASED(KEY::RIGHT))
	{
		vPos += Vec2(-1.f, 0.f) * 40000.f * DT;
		GetObj()->SetPos(vPos);
		GetRigidBody()->SetWall(false);
		GetFSM()->ChangeState(L"FALL");
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

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetFSM()->ChangeState(L"WALL_IDLE");
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetFSM()->ChangeState(L"WALL_IDLE");
		}

		return;
	}
}

void CState_WallEnter::Exit()
{
}