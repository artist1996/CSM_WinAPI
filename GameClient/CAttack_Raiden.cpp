#include "pch.h"
#include "CAttack_Raiden.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAttack_Raiden::CAttack_Raiden()
	: m_Owner(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
}

CAttack_Raiden::CAttack_Raiden(CObj* _Owner, CAnimator* _Animator)
	: m_Owner(_Owner)
	, m_Animator(_Animator)
{
	// Info
	SetPos(_Owner->GetPos());
	SetScale(Vec2(10.f, 10.f));
	
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);	
}

CAttack_Raiden::~CAttack_Raiden()
{
}

void CAttack_Raiden::tick()
{
	CObj::tick();

	if (m_Owner->IsDead())
	{
		Destroy();
		return;
	}

	Attack();
}

void CAttack_Raiden::Attack()
{
	if (!m_Owner->IsDead())
	{
		if (0 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(100.f, -180.f));
			m_Collider->SetScale(Vec2(50.f, 60.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(90.f, -195.f));
			m_Collider->SetScale(Vec2(55.f, 65.f));
		}

		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(80.f, -235.f));
			m_Collider->SetScale(Vec2(55.f, 70.f));
		}

		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-50.f, -120.f));
			m_Collider->SetScale(Vec2(280.f, 270.f));
		}

		if (4 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			Destroy();
			return;
		}
	}
}
