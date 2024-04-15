#include "pch.h"
#include "CBoss_Breath.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAnimation.h"
#include "CAttack_Breath.h"

CBoss_Breath::CBoss_Breath()
	: m_Count(0)
	, m_Dir(0.f)
	, m_Time(0.f)
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

	m_Animation = true;

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

	if (1.f == m_Dir && L"JUMP_RIGHT" == GetAnimator()->GetCurAnim()->GetName())
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		if (vPos.x < (pTargetPlatform->GetPos().x + pTargetPlatform->GetScale().x * 0.5f) - 100.f)
		{
			vPos.x += 1.f * 900.f * DT;
			GetObj()->SetPos(vPos);
		}
	}

	if (-1.f == m_Dir && L"JUMP_LEFT" == GetAnimator()->GetCurAnim()->GetName())
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
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
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->Play(L"BREATH_RIGHT", false);
		}

		else if (1.f == m_Dir)
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->Play(L"BREATH_LEFT", false);
		}

		m_Animation = false;
	}

	if (L"BREATH_LEFT" == GetAnimator()->GetCurAnim()->GetName()
		|| L"BREATH_RIGHT" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (2 == GetAnimator()->GetCurAnim()->GetCurFrameIdx())
		{
			m_Attack = true;
		}
	}
	
	if (m_Attack)
	{
		m_Time += DT;
	}
	
	if (0.2f <= m_Time && 20 > m_Count)
	{
		CAttack_Breath* pAttack = new CAttack_Breath(GetObj());
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_ATTACK, pAttack);
		m_Time = 0.f;
		++m_Count;
	}

	if (L"BREATH_LEFT" == GetAnimator()->GetCurAnim()->GetName()
		|| L"BREATH_RIGHT" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->IsFinish())
		{
			if (DIRECTION::RIGHT == GetObj()->GetDirection())
			{
				GetObj()->SetDirection(DIRECTION::LEFT);
			}

			else if (DIRECTION::LEFT == GetObj()->GetDirection())
			{
				GetObj()->SetDirection(DIRECTION::RIGHT);
			}
			GetFSM()->ChangeState(L"IDLE");
		}
	}
}

void CBoss_Breath::Exit()
{
	GetRigidBody()->SetJumpSpeed(700.f);
	m_Count = 0;
	m_Attack = false;
	m_Animation = false;
	m_Time = 0.f;
}