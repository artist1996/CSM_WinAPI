#include "pch.h"
#include "CAttack_Hadouken.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAttack_Hadouken::CAttack_Hadouken()
	: m_Owner(nullptr)
{
}

CAttack_Hadouken::CAttack_Hadouken(CObj* _Owner, Vec2 _Pos)
	: m_Owner(_Owner)
{
	// Info
	SetPos(_Pos);
	SetScale(Vec2(200.f, 50.f));

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	
	// Collider
	if (DIRECTION::LEFT == m_Owner->GetDirection())
	{
		SetDirection(DIRECTION::LEFT);
		m_Collider->SetOffsetPos(Vec2(-150.f, -40.f));
	}

	else
	{
		SetDirection(DIRECTION::RIGHT);
		m_Collider->SetOffsetPos(Vec2(150.f, -40.f));
	}
	m_Collider->SetScale(GetScale());
	
	// Animator
	m_Animator->LoadAnimation(L"animation\\boss\\attack\\left\\HADOUKEN_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\attack\\right\\HADOUKEN_RIGHT.anim");

	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		m_Animator->Play(L"HADOUKEN_RIGHT", false);
	}

	else
	{
		m_Animator->Play(L"HADOUKEN_LEFT", false);
	}
}

CAttack_Hadouken::~CAttack_Hadouken()
{
}


void CAttack_Hadouken::tick()
{
	CObj::tick();
	
	Vec2 vPos = GetPos();

	if (m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
	
	if (DIRECTION::RIGHT == GetDirection())
	{
		vPos += Vec2(1.f, 0.f) * 100.f * DT;
	}

	else
	{
		vPos += Vec2(-1.f, 0.f) * 100.f * DT;
	}

	SetPos(vPos);
}
