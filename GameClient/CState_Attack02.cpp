#include "pch.h"
#include "CState_Attack02.h"
#include "CPlayer.h"

CState_Attack02::CState_Attack02()
	: m_bNext(false)
{
}

CState_Attack02::~CState_Attack02()
{
}


void CState_Attack02::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"ATTACK02_RIGHT", false);
		dynamic_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK02);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"ATTACK02_LEFT", false);
		dynamic_cast<CPlayer*>(GetObj())->CreateAttack(ATTACK_TYPE::ATTACK02);
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