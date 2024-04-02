#include "pch.h"
#include "CPlayer_JumpAttack.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CAnimator.h"

CPlayer_JumpAttack::CPlayer_JumpAttack()
	: m_Owner(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
{
}

CPlayer_JumpAttack::CPlayer_JumpAttack(CObj* _Owner, CAnimator* _Animator, Vec2 _Pos)
	: m_Owner(_Owner)
	, m_Animator(_Animator)
{
	SetPos(_Pos);
	m_Collider = (CCollider*)AddComponent(new CCollider);
}

CPlayer_JumpAttack::~CPlayer_JumpAttack()
{
}

void CPlayer_JumpAttack::tick()
{
	CObj::tick();

	if (m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
	
	if (DIRECTION::RIGHT == m_Owner->GetDirection() && L"RAKUOUHA_RIGHT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}

	if (DIRECTION::LEFT == m_Owner->GetDirection() && L"RAKUOUHA_LEFT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}
	JumpAttack();

	Vec2 vPos = m_Owner->GetPos();
	
	
	SetPos(vPos);
}

void CPlayer_JumpAttack::JumpAttack()
{
	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		if (0 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(45.f, -130.f));
			m_Collider->SetScale(Vec2(125.f, 140.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(75.f, -110.f));
			m_Collider->SetScale(Vec2(105.f, 165.f));
		}

		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(50.f, -40.f));
			m_Collider->SetScale(Vec2(150.f, 80.f));
		}
		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(5.f, -20.f));
			m_Collider->SetScale(Vec2(125.f, 90.f));
		}
		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-40.f, -30.f));
			m_Collider->SetScale(Vec2(120.f, 130.f));
		}
		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-68.f, -70.f));
			m_Collider->SetScale(Vec2(105.f, 135.f));
		}
		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-55.f, -150.f));
			m_Collider->SetScale(Vec2(145.f, 80.f));
		}
		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-5.f, -150.f));
			m_Collider->SetScale(Vec2(125.f, 100.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx() && 0.025 <= m_Animator->GetCurAnim()->GetFrame(7).Duration)
		{
			Destroy();
		}
	}

	else if (DIRECTION::LEFT == m_Owner->GetDirection())
	{
		if (0 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-45.f, -130.f));
			m_Collider->SetScale(Vec2(125.f, 140.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-75.f, -110.f));
			m_Collider->SetScale(Vec2(105.f, 165.f));
		}

		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-50.f, -40.f));
			m_Collider->SetScale(Vec2(150.f, 80.f));
		}
		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-5.f, -20.f));
			m_Collider->SetScale(Vec2(125.f, 90.f));
		}
		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(40.f, -30.f));
			m_Collider->SetScale(Vec2(120.f, 130.f));
		}
		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(68.f, -70.f));
			m_Collider->SetScale(Vec2(105.f, 135.f));
		}
		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(55.f, -150.f));
			m_Collider->SetScale(Vec2(145.f, 80.f));
		}
		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(5.f, -150.f));
			m_Collider->SetScale(Vec2(125.f, 100.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx() && 0.025 <= m_Animator->GetCurAnim()->GetFrame(7).Duration)
		{
			Destroy();
		}
	}
}