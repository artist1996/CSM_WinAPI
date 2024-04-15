#include "pch.h"
#include "CState_Landing.h"
#include "CPlayerEffectMgr.h"

#include "CSound.h"

CState_Landing::CState_Landing()
	: m_pSound(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"LANDING", L"sound\\zero\\LANDING.wav");
}

CState_Landing::~CState_Landing()
{
}

void CState_Landing::Enter()
{
	m_pSound->Play();
	Initialize();
	
	GetRigidBody()->SetWall(false);

	GetCollider()->SetScale(Vec2(70.f, 105.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"LANDING_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"LANDING_LEFT", false);
	}
}

void CState_Landing::FinalTick()
{
	if (KEY_PRESSED(KEY::Z) && KEY_TAP(KEY::X))
	{

		CPlayerEffectMgr::GetInst()->SetActive(true);
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			CPlayerEffectMgr::GetInst()->Play(L"JUMP_RIGHT", true);
			CPlayerEffectMgr::GetInst()->SetActive(true);
		}
		else
		{
			CPlayerEffectMgr::GetInst()->Play(L"JUMP_LEFT", true);
			CPlayerEffectMgr::GetInst()->SetActive(true);
		}
		GetObj()->SetSpeed(500.f);
		GetFSM()->ChangeState(L"JUMP");
		return;
	}

	if (GetAnimator()->GetCurAnim()->IsFinish() && GetRigidBody()->IsBlock())
	{
		GetFSM()->ChangeState(L"BLOCK");
		return;
	}


	if (GetAnimator()->GetCurAnim()->IsFinish() && !GetRigidBody()->IsBlock())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CState_Landing::Exit()
{
}