#include "pch.h"
#include "CBoss_Dead.h"
#include "CAnimation.h"
#include "CSoundMgr.h"

CBoss_Dead::CBoss_Dead()
	: m_First(true)
{
}

CBoss_Dead::~CBoss_Dead()
{
}

void CBoss_Dead::Enter()
{
	Initialize();
	
	GetRigidBody()->UseGravity(true);

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DEAD_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DEAD_LEFT", false);
	}
}

void CBoss_Dead::FinalTick()
{
	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		// 플레이어 FSM 변경
		if (m_First)
		{
			CFSM* pFSM = pTarget->GetComponent<CFSM>();
			pFSM->ChangeState(L"VICTORY");
			m_First = false;
			CSoundMgr::GetInst()->RegisterToBGM(nullptr);
		}
	}
}

void CBoss_Dead::Exit()
{
}