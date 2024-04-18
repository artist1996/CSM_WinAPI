#include "pch.h"
#include "CState_Dash.h"
#include "CEffect_Dash.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CPlayerEffectMgr.h"
#include "CAfterImage.h"

#include "CSound.h"

CState_Dash::CState_Dash()
	: m_AfterImg(false)
	, m_pSound(nullptr)
	, m_bSound(true)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"DASH", L"sound\\zero\\DASH.wav");
}

CState_Dash::~CState_Dash()
{
}

void CState_Dash::Enter()
{
	Initialize();
	
	m_AfterImg = true;

	if (GetObj()->IsBlack())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_DASH_RIGHT", false);
			CPlayerEffectMgr::GetInst()->DashSetPos(Vec2(GetObj()->GetPos().x - 80.f, GetObj()->GetPos().y));
			CPlayerEffectMgr::GetInst()->PlayDash(L"EFFECT_DASH_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_DASH_LEFT", false);
			CPlayerEffectMgr::GetInst()->DashSetPos(Vec2(GetObj()->GetPos().x + 80.f, GetObj()->GetPos().y));
			CPlayerEffectMgr::GetInst()->PlayDash(L"EFFECT_DASH_LEFT", false);
		}
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"DASH_RIGHT", false);
			CPlayerEffectMgr::GetInst()->DashSetPos(Vec2(GetObj()->GetPos().x - 80.f, GetObj()->GetPos().y));
			CPlayerEffectMgr::GetInst()->PlayDash(L"EFFECT_DASH_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"DASH_LEFT", false);
			CPlayerEffectMgr::GetInst()->DashSetPos(Vec2(GetObj()->GetPos().x + 80.f, GetObj()->GetPos().y));
			CPlayerEffectMgr::GetInst()->PlayDash(L"EFFECT_DASH_LEFT", false);
		}
	}
}

void CState_Dash::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();
	
	if (2 == GetAnimator()->GetCurAnim()->GetCurFrameIdx())
	{
		if (m_bSound)
		{
			m_pSound->Play();
			m_bSound = false;
		}

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
		//CPlayerEffectMgr::GetInst()->SetActive(false);
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	if (KEY_TAP(KEY::X))
	{
		CPlayerEffectMgr::GetInst()->SetActive(true);
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			CPlayerEffectMgr::GetInst()->Play(L"JUMP_RIGHT", true);
		}

		else
		{
			CPlayerEffectMgr::GetInst()->Play(L"JUMP_LEFT", true);
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
				CPlayerEffectMgr::GetInst()->Play(L"DASH_RIGHT", true);
				CPlayerEffectMgr::GetInst()->SetActive(true);
				
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
				CPlayerEffectMgr::GetInst()->Play(L"DASH_LEFT", true);
				CPlayerEffectMgr::GetInst()->SetActive(true);

				m_AfterImg = false;
			}
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
	m_AfterImg = false;
	m_bSound = true;
}