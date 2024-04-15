#include "pch.h"
#include "CAttack_Breath.h"

#include "CCollider.h"
#include "CAnimator.h"

CAttack_Breath::CAttack_Breath()
	: m_Owner(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Dir(0.f)
	, m_Play(true)
{
}

CAttack_Breath::CAttack_Breath(CObj* _Owner)
	: m_Owner(_Owner)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Dir(0.f)
	, m_Play(true)
{
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animator
	m_Animator->LoadAnimation(L"animation\\boss\\attack\\left\\EFFECT_BREATH_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\attack\\right\\EFFECT_BREATH_RIGHT.anim");

	// Info
	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		SetPos(m_Owner->GetPos().x + 100.f, m_Owner->GetPos().y);
		m_Dir = 1.f;
	}

	else if(DIRECTION::LEFT == m_Owner->GetDirection())
	{
		SetPos(m_Owner->GetPos().x - 100.f, m_Owner->GetPos().y);
		m_Dir = -1.f;
	}

	SetScale(Vec2(70.f, 70.f));
	m_CenterPos = m_Owner->GetPos();

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -30.f));
	m_Collider->SetScale(GetScale());

	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		m_Animator->Play(L"EFFECT_BREATH_RIGHT", true);
	}

	else
	{
		m_Animator->Play(L"EFFECT_BREATH_LEFT", true);
	}
}

CAttack_Breath::~CAttack_Breath()
{
}

void CAttack_Breath::tick()
{
	CObj::tick();
	
	Vec2 vPos = GetPos();

	if (abs(m_CenterPos.x - vPos.x) > 700.f)
	{
		Destroy();
	}
	
	if (1.f == m_Dir)
	{
		vPos += Vec2(1.f, 0.f) * 400.f * DT;
	}

	else if(-1.f == m_Dir)
	{
		vPos += Vec2(-1.f, 0.f) * 400.f * DT;
	}

	SetPos(vPos);
}