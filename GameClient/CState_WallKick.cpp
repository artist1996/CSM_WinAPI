#include "pch.h"
#include "CState_WallKick.h"

CState_WallKick::CState_WallKick()
	: m_bAirMove(false)
{
}

CState_WallKick::~CState_WallKick()
{
}


void CState_WallKick::Enter()
{
	Initialize();
	GetRigidBody()->Jump();
	if (DIRECTION::RIGHT == GetObj()->GetDirection())

	{
		GetAnimator()->Play(L"WALLKICK_RIGHT", false);
	}
	
	else if(DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"WALLKICK_LEFT", false);
	}
}

void CState_WallKick::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (2 > GetAnimator()->GetCurAnim()->GetCurFrameIdx())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			vPos += Vec2(-1.f, 0.f) * (GetObj()->GetSpeed() + 100.f) * DT;
			GetObj()->SetPos(vPos);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			vPos += Vec2(1.f, 0.f) * (GetObj()->GetSpeed() + 100.f) * DT;
			GetObj()->SetPos(vPos);
		}
	}

	if (!GetAnimator()->GetCurAnim()->IsFinish())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			if (KEY_PRESSED(KEY::RIGHT))
			{
				m_bAirMove = true;
			}
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			if (KEY_PRESSED(KEY::LEFT))
			{
				m_bAirMove = true;
			}
		}
	}

	if (m_bAirMove)
	{
		if (2 >= GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			if (DIRECTION::RIGHT == GetObj()->GetDirection())
			{
				if (KEY_PRESSED(KEY::RIGHT))
				{
					GetObj()->SetDirection(DIRECTION::RIGHT);
					vPos += Vec2(1.f, 0.f) * 300.f * DT;
					GetObj()->SetPos(vPos);
				}

				else if (KEY_TAP(KEY::LEFT))
				{
					GetObj()->SetDirection(DIRECTION::LEFT);
					GetFSM()->ChangeState(L"FALL");
				}
			}
			
			else if (DIRECTION::LEFT == GetObj()->GetDirection())
			{
				if (KEY_PRESSED(KEY::LEFT))
				{
					GetObj()->SetDirection(DIRECTION::LEFT);
					vPos += Vec2(-1.f, 0.f) * 300.f * DT;
					GetObj()->SetPos(vPos);
				}

				else if (KEY_TAP(KEY::RIGHT))
				{
					GetObj()->SetDirection(DIRECTION::RIGHT);
					GetFSM()->ChangeState(L"FALL");
				}
			}
		}
	}

	if (m_bAirMove && GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"FALL");
		return;
	}

	else if (!m_bAirMove)
	{
		if (GetAnimator()->GetCurAnim()->IsFinish())
		{
			GetFSM()->ChangeState(L"FALL");
			return;
		}
	}
}

void CState_WallKick::Exit()
{
	m_bAirMove = false;
}