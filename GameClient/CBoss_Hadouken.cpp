#include "pch.h"
#include "CBoss_Hadouken.h"

#include "CAnimation.h"

CBoss_Hadouken::CBoss_Hadouken()
{
}

CBoss_Hadouken::~CBoss_Hadouken()
{
}

void CBoss_Hadouken::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"HADOUKEN_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"HADOUKEN_LEFT", false);
	}
}

void CBoss_Hadouken::FinalTick()
{
	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
	}
}

void CBoss_Hadouken::Exit()
{
}