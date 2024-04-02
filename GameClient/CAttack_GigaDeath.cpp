#include "pch.h"
#include "CAttack_GigaDeath.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"


CAttack_GigaDeath::CAttack_GigaDeath()
	: m_Animator(nullptr)
{
}

CAttack_GigaDeath::CAttack_GigaDeath(Vec2 _Pos, Vec2 _Scale)
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_CenterPos(_Pos)
	, m_Speed(300.f)
	, m_MaxDistance(400.f)
{
	// Info
	SetPos(_Pos);
	SetScale(_Scale);

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -30.f));
	m_Collider->SetScale(_Scale);

	// Animation
	m_Animator->LoadAnimation(L"animation\\monster\\gigadeath\\missile.anim");
	m_Animator->Play(L"missile", true);
}

CAttack_GigaDeath::~CAttack_GigaDeath()
{
}

void CAttack_GigaDeath::tick()
{
	CObj::tick();
	
	Vec2 vPos = GetPos();

	vPos += Vec2(-1.f, 0.f) * m_Speed * DT;
	
	float fDist = fabs(m_CenterPos.x - vPos.x) - m_MaxDistance;
	if (400.f < fDist)
	{
		Destroy();
		return;
	}

	SetPos(vPos);
}