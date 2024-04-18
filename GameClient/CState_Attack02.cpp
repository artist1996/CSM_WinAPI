#include "pch.h"
#include "CState_Attack02.h"
#include "CPlayer.h"

#include "CSound.h"

CState_Attack02::CState_Attack02()
	: m_bNext(false)
	, m_pSound(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"ATTACK02", L"sound\\zero\\ATTACK02.wav");
}

CState_Attack02::~CState_Attack02()
{
}


void CState_Attack02::Enter()
{
	m_pSound->Play();

	Initialize();

	if (GetObj()->IsBlack())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_ATTACK02_RIGHT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK02);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_ATTACK02_LEFT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK02);
		}
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"ATTACK02_RIGHT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK02);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"ATTACK02_LEFT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK02);
		}
	}
}

void CState_Attack02::FinalTick()
{
	if (KEY_TAP(KEY::C))
	{
		m_bNext = true;        
	}

	if (m_bNext)
	{
		if (5 <= GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			GetFSM()->ChangeState(L"ATTACK03");
			return;
		}
	}
	
	else if (!m_bNext)
	{
		if (GetAnimator()->GetCurAnim()->IsFinish())
		{
			GetFSM()->ChangeState(L"IDLE");
			return;
		}
	}
}

void CState_Attack02::Exit()
{
	m_bNext = false;
}