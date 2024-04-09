#include "pch.h"
#include "CAttack_DiveKick.h"

#include "CCollider.h"
#include "CAnimator.h"

CAttack_DiveKick::CAttack_DiveKick()
	: m_Owner(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
}

CAttack_DiveKick::CAttack_DiveKick(CObj* _Owner)
	: m_Owner(_Owner)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
	// Info
	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		SetPos(_Owner->GetPos().x + 50.f, 1100.f);
	}

	else
	{
		SetPos(_Owner->GetPos().x - 50.f, 1100.f);
	}
	SetScale(70.f, 60.f);

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -35.f));
	m_Collider->SetScale(GetScale());

	// Animator
	m_Animator->LoadAnimation(L"animation\\boss\\attack\\right\\DIVEKICK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\attack\\left\\DIVEKICK_LEFT.anim");
	
	// Animation

	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		m_Animator->Play(L"DIVEKICK_RIGHT", true);
	}

	else
	{
		m_Animator->Play(L"DIVEKICK_LEFT", true);
	}

}

CAttack_DiveKick::~CAttack_DiveKick()
{
}

void CAttack_DiveKick::tick()
{
	CObj::tick();

	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		SetPos(m_Owner->GetPos().x + 70.f, m_Owner->GetPos().y + 20.f);
	}

	else
	{
		SetPos(m_Owner->GetPos().x - 60.f, m_Owner->GetPos().y + 25.f);
	}
}