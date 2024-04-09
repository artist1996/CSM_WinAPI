#include "pch.h"
#include "CBoss_DiveKick.h"
#include "CLevelMgr.h"

#include "CAttack_DiveKick.h"


CBoss_DiveKick::CBoss_DiveKick()
	: m_bDown(false)
	, m_bUP(true)
	, m_bFirst(true)
	, m_DiveKick(nullptr)
{
}

CBoss_DiveKick::~CBoss_DiveKick()
{
}

void CBoss_DiveKick::Enter()
{
	Initialize();

	m_CenterPos = GetObj()->GetPos();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DIVEKICK_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DIVEKICK_LEFT", false);
	}

	CObj* pTarget = GetBlackboardData<CObj*>(L"Target");
	m_Dir = pTarget->GetPos() - GetObj()->GetPos();

	if (!m_Dir.IsZero())
	{
		m_Dir.Normalize();
	}

	m_bUP = true;
	GetRigidBody()->Jump();
}

void CBoss_DiveKick::FinalTick()
{
	CObj* pTargetPlatform = GetBlackboardData<CObj*>(L"TargetPlatform");
	Vec2 vPos = GetObj()->GetPos();

	if (m_bUP)
	{
		if (m_CenterPos.y - GetObj()->GetPos().y > 200.f)
		{
			m_bUP = false;
			m_bDown = true;
			GetRigidBody()->UseGravity(false);
		}
	}

	

	if (m_bDown)
	{
		if (m_bFirst)
		{
			m_DiveKick = new CAttack_DiveKick(GetObj());
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_ATTACK, m_DiveKick);
			m_bFirst = false;
		}
		
		if (m_Dir.x < 0.f && vPos.x > (pTargetPlatform->GetPos().x - pTargetPlatform->GetScale().x * 0.5f) + 100.f)
		{
			vPos += Vec2(m_Dir.x, 1.f) * 500.f * DT;
		}

		else if (m_Dir.x > 0.f && vPos.x < (pTargetPlatform->GetPos().x + pTargetPlatform->GetScale().x * 0.5f) - 100.f)
		{
			vPos += Vec2(m_Dir.x, 1.f) * 500.f * DT;
		}
		
		if (m_Dir.x < 0.f && vPos.x < (pTargetPlatform->GetPos().x - pTargetPlatform->GetScale().x * 0.5f) + 100.f)
		{
			vPos.y += 1.f * 500.f * DT;
		}

		else if (m_Dir.x > 0.f && vPos.x > (pTargetPlatform->GetPos().x + pTargetPlatform->GetScale().x * 0.5f) - 100.f)
		{
			vPos.y += 1.f * 500.f * DT;
		}

		GetObj()->SetPos(vPos);
	}

	if (GetRigidBody()->IsGround())
	{
		m_DiveKick->Destroy();
		GetFSM()->ChangeState(L"IDLE");
	}
	
}

void CBoss_DiveKick::Exit()
{
	GetRigidBody()->UseGravity(true);
	m_bUP = true;
	m_bFirst = true;
	m_bDown = false;
	m_DiveKick = nullptr;
}