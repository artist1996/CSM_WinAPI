#include "pch.h"
#include "CAttack_Soryugen.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAttack_Soryugen::CAttack_Soryugen()
	: m_Owner(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_eType(ATTACK_TYPE::END)
{
}

CAttack_Soryugen::CAttack_Soryugen(CObj* _Owner, ATTACK_TYPE _Type)
	: m_Owner(_Owner)
	, m_eType(_Type)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
	// Info
	SetScale(Vec2(100.f, 100.f));

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -100.f));
	m_Collider->SetScale(GetScale());

	// Animator
	m_Animator->LoadAnimation(L"animation\\boss\\attack\\SORYUGEN.anim");

	// Animation
	m_Animator->Play(L"SORYUGEN", true);
}

CAttack_Soryugen::~CAttack_Soryugen()
{
}

void CAttack_Soryugen::tick()
{
	CObj::tick();

	if (m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}

	if (DIRECTION::LEFT == m_Owner->GetDirection())
	{
		if (ATTACK_TYPE::ATTACK01 == m_eType)
		{
			SetPos(m_Owner->GetPos().x - 60.f, m_Owner->GetPos().y - 100.f);
		}

		else if (ATTACK_TYPE::ATTACK02 == m_eType)
		{
			SetPos(m_Owner->GetPos().x - 60.f, m_Owner->GetPos().y - 50.f);
		}
	}

	else
	{
		if (ATTACK_TYPE::ATTACK01 == m_eType)
		{
			SetPos(m_Owner->GetPos().x + 70.f, m_Owner->GetPos().y - 100.f);
		}

		else if (ATTACK_TYPE::ATTACK02 == m_eType)
		{
			SetPos(m_Owner->GetPos().x + 70.f, m_Owner->GetPos().y - 50.f);
		}
	}
}