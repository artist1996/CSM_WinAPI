#include "pch.h"
#include "CState_Dash.h"
#include "CEffect_Dash.h"
#include "CLevelMgr.h"
#include "CLevel.h"

CState_Dash::CState_Dash()
{
}

CState_Dash::~CState_Dash()
{
}

void CState_Dash::Enter()
{
	Initialize();
	
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
			GetCollider()->SetScale(Vec2(130.f, 80.f));
			GetCollider()->SetOffsetPos(Vec2(17.f, -35.f));
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetCollider()->SetScale(Vec2(130.f, 80.f));
			GetCollider()->SetOffsetPos(Vec2(0.f, -35.f));
		}
	}

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	if (KEY_TAP(KEY::X))
	{
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
			vPos += Vec2(1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
			return;
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection() && 2 < GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			vPos += Vec2(-1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
			return;
		}
	}

	else if (KEY_RELEASED(KEY::Z))
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CState_Dash::Exit()
{
}