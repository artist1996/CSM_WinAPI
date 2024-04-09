#include "pch.h"
#include "CAttack_Soryugen.h"

#include "CCollider.h"
#include "CAnimator.h"

CAttack_Soryugen::CAttack_Soryugen()
	: m_Owner(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
}

CAttack_Soryugen::CAttack_Soryugen(CObj* _Owner)
	: m_Owner(_Owner)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
	// Info
	SetScale(Vec2(50.f, 50.f));

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Collider
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
}