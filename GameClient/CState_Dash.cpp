#include "pch.h"
#include "CState_Dash.h"
#include "CEffect_Dash.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CShadowMgr.h"
#include "CAfterImage.h"

CState_Dash::CState_Dash()
	: m_AfterImg(false)
{
}

CState_Dash::~CState_Dash()
{
}

void CState_Dash::Enter()
{
	Initialize();
	
	m_AfterImg = true;

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DASH_RIGHT", false);
		CEffect_Dash* pEffect = new CEffect_Dash(GetObj(), Vec2(GetObj()->GetPos().x - 60.f, GetObj()->GetPos().y), Vec2(20.f,20.f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DASH_LEFT", false);
		CEffect_Dash* pEffect = new CEffect_Dash(GetObj(), Vec2(GetObj()->GetPos().x + 60.f, GetObj()->GetPos().y), Vec2(20.f, 20.f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
	}
}

void CState_Dash::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();
	
	if (2 == GetAnimator()->GetCurAnim()->GetCurFrameIdx())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetCollider()->SetScale(Vec2(70.f, 80.f));
			GetCollider()->SetOffsetPos(Vec2(17.f, -35.f));
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetCollider()->SetScale(Vec2(70.f, 80.f));
			GetCollider()->SetOffsetPos(Vec2(0.f, -35.f));
		}
	}

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		//CShadowMgr::GetInst()->SetActive(false);
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	if (KEY_TAP(KEY::X))
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			CShadowMgr::GetInst()->Play(L"JUMP_RIGHT", true);
		}

		else
		{
			CShadowMgr::GetInst()->Play(L"JUMP_LEFT", true);
		}
		GetObj()->SetSpeed(500.f);
		GetFSM()->ChangeState(L"JUMP");
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

	if (KEY_PRESSED(KEY::Z))
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection() && 2 < GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			if (m_AfterImg)
			{
				CShadowMgr::GetInst()->Play(L"DASH_RIGHT", true);
				CShadowMgr::GetInst()->SetActive(true);
				
				m_AfterImg = false;
			}

			vPos += Vec2(1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
			return;
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection() && 2 < GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			if (m_AfterImg)
			{
				CShadowMgr::GetInst()->Play(L"DASH_LEFT", true);
				CShadowMgr::GetInst()->SetActive(true);

				m_AfterImg = false;
			}
			vPos += Vec2(-1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
			return;
		}
	}

	else if (KEY_RELEASED(KEY::Z))
	{
		//CShadowMgr::GetInst()->SetActive(false);
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CState_Dash::Exit()
{
	m_AfterImg = false;
}