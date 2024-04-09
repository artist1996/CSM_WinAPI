#include "pch.h"
#include "CBoss_Soryugen.h"
#include "CAnimation.h"

CBoss_Soryugen::CBoss_Soryugen()
	: m_Fall(true)
{
}

CBoss_Soryugen::~CBoss_Soryugen()
{
}


void CBoss_Soryugen::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"SORYUGEN_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"SORYUGEN_LEFT", false);
	}

	GetRigidBody()->Jump();
}

void CBoss_Soryugen::FinalTick()
{
	CObj* pTargetPlatform = GetBlackboardData<CObj*>(L"TargetPlatform");
	Vec2 vPos = GetObj()->GetPos();

	if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		if (vPos.x > (pTargetPlatform->GetPos().x - pTargetPlatform->GetScale().x * 0.5f) + 100.f)
		{
			vPos += Vec2(-1.f, 0.f) * 200.f * DT;
		}
	}

	else if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		if (vPos.x < (pTargetPlatform->GetPos().x + pTargetPlatform->GetScale().x * 0.5f) - 100.f)
		{
			vPos += Vec2(1.f, 0.f) * 200.f * DT;
		}
	}

	GetObj()->SetPos(vPos);

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetRigidBody()->SetJump(false);

		if (m_Fall)
		{
			if (DIRECTION::RIGHT == GetObj()->GetDirection())
			{
				GetAnimator()->Play(L"FALL_RIGHT", false);
			}

			else
			{
				GetAnimator()->Play(L"FALL_LEFT", false);
			}

			m_Fall = false;
		}
	}

	if (GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"IDLE");
	}
	
}

void CBoss_Soryugen::Exit()
{
	m_Fall = true;
}