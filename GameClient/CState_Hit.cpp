#include "pch.h"
#include "CState_Hit.h"

#include "CPlayerEffectMgr.h"
#include "CSound.h"

CState_Hit::CState_Hit()
	: m_pSound(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"HIT", L"sound\\zero\\HIT.wav");
}

CState_Hit::~CState_Hit()
{
}

void CState_Hit::Enter()
{
	m_pSound->Play();
	Initialize();

	CPlayerEffectMgr::GetInst()->SetActive(false);

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"HIT_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"HIT_LEFT", false);
	}
}

void CState_Hit::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			vPos += Vec2(-1.f, 0.f) * 50.f * DT;
			GetObj()->SetPos(vPos);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			vPos += Vec2(1.f, 0.f) * 50.f * DT;
			GetObj()->SetPos(vPos);
		}
		return;
	}
}

void CState_Hit::Exit()
{
}