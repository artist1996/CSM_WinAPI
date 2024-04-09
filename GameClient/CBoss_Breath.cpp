#include "pch.h"
#include "CBoss_Breath.h"

#include "CAnimation.h"

CBoss_Breath::CBoss_Breath()
	: m_Count(0)
	, m_Dir(0.f)
	, m_Animation(true)
{
}

CBoss_Breath::~CBoss_Breath()
{
}

void CBoss_Breath::Enter()
{
	Initialize();

	CObj* pTargetPlatform = GetBlackboardData<CObj*>(L"TargetPlatform");
	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");

	Vec2 vPos = GetObj()->GetPos();

	if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		m_Dir = -1.f;
		GetAnimator()->Play(L"JUMP_LEFT", false);
		GetRigidBody()->SetJumpSpeed(300.f);
		GetRigidBody()->Jump();
	}

	else if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		m_Dir = 1.f;
		GetAnimator()->Play(L"JUMP_RIGHT", false);
		GetRigidBody()->SetJumpSpeed(300.f);
		GetRigidBody()->Jump();
	}
}

void CBoss_Breath::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();
	CObj* pTargetPlatform = GetBlackboardData<CObj*>(L"TargetPlatform");

	if (1.f == m_Dir)
	{
		if (vPos.x < (pTargetPlatform->GetPos().x + pTargetPlatform->GetScale().x * 0.5f) - 100.f)
		{
			vPos.x += 1.f * 900.f * DT;
			GetObj()->SetPos(vPos);
		}
	}

	if (-1.f == m_Dir)
	{
		if (vPos.x > (pTargetPlatform->GetPos().x - pTargetPlatform->GetScale().x * 0.5f) + 100.f)
		{
			vPos.x += m_Dir * 900.f * DT;
			GetObj()->SetPos(vPos);
		}
	}

	if (GetRigidBody()->IsGround() && m_Animation)
	{
		if (-1.f == m_Dir)
		{
			//GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->Play(L"BREATH_RIGHT", false);
		}

		else 
		{
			//GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->Play(L"BREATH_LEFT", false);
		}

		m_Animation = false;
	}

	if (L"BREATH_LEFT" == GetAnimator()->GetCurAnim()->GetName()
		|| L"BREATH_RIGHT" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->IsFinish())
		{
			GetFSM()->ChangeState(L"IDLE");
		}
	}
}

void CBoss_Breath::Exit()
{
	GetRigidBody()->SetJumpSpeed(700.f);
	m_Count = 0;
	m_Animation = true;
}