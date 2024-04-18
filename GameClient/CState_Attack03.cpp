#include "pch.h"
#include "CState_Attack03.h"
#include "CPlayer.h"

#include "CSound.h"

CState_Attack03::CState_Attack03()
	: m_pSound(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"ATTACK03", L"sound\\zero\\ATTACK03.wav");
}

CState_Attack03::~CState_Attack03()
{
}

void CState_Attack03::Enter()
{
	m_pSound->Play();

	Initialize();

	if (GetObj()->IsBlack())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_ATTACK03_RIGHT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK03);
		}

		if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_ATTACK03_LEFT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK03);
		}
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"ATTACK03_RIGHT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK03);
		}

		if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"ATTACK03_LEFT", false);
			static_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK03);
		}
	}
}

void CState_Attack03::FinalTick()
{
	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}
}

void CState_Attack03::Exit()
{
}