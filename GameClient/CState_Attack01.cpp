#include "pch.h"
#include "CState_Attack01.h"
#include "CPlayer.h"
#include "CSound.h"

CState_Attack01::CState_Attack01()
	: m_bNext(false)
	, m_pSound(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"ATTACK01", L"sound\\zero\\ATTACK01.wav");
}

CState_Attack01::~CState_Attack01()
{
}

void CState_Attack01::Enter()
{
	m_pSound->Play();
	Initialize();

	GetCollider()->SetScale(Vec2(90.f, 100.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));

	if (GetObj()->IsBlack())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_ATTACK01_RIGHT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK01);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_ATTACK01_LEFT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK01);
		}
	}
	
	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"ATTACK01_RIGHT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK01);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"ATTACK01_LEFT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK01);
		}
	}
}

void CState_Attack01::FinalTick()
{
	if (KEY_TAP(KEY::Z))
	{
		GetObj()->SetSpeed(500.f);
		GetFSM()->ChangeState(L"DASH");
		return;
	}
	
	if (KEY_TAP(KEY::C) && !GetAnimator()->GetCurAnim()->IsFinish())
	{
		m_bNext = true;
	}

	if (m_bNext)
	{
		if (8 <= GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			GetFSM()->ChangeState(L"ATTACK02");
			return;
		}
	}

	else if (!m_bNext)
	{
		if (GetAnimator()->GetCurAnim()->IsFinish())
		{
			GetFSM()->ChangeState(L"IDLE");
		}
	}
}

void CState_Attack01::Exit()
{
	m_bNext = false;
}