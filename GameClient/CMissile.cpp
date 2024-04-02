#include "pch.h"
#include "CMissile.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CTimeMgr.h"

CMissile::CMissile()
	: m_Owner(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Speed(300.f)
	, m_Dir(0.f)
	, m_MaxDistance(400.f)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(30.f, 30.f));
}

CMissile::CMissile(Vec2 _Pos, Vec2 _Scale, CObj* _Owner)
	: m_Owner(_Owner)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Speed(300.f)
	, m_Dir(0.f)
{
	// Info
	SetPos(_Pos);
	SetScale(_Scale);
	m_CenterPos = _Pos;

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);


	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -7.f));
	m_Collider->SetScale(Vec2(20.f,15.f));

	// Animation
	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\missile.anim");


	// Dir
	if (DIRECTION::LEFT == m_Owner->GetDirection())
	{
		m_Dir = -1.f;
	}

	else if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		m_Dir = 1.f;
	}

	m_Animator->Play(L"missile", true);
}

CMissile::~CMissile()
{
	
}

void CMissile::tick()
{
	CObj::tick();
	Vec2 vPos = GetPos();
	
	vPos.x += m_Dir * m_Speed * DT;
	
	float fDist = fabs(m_CenterPos.x - vPos.x) - m_MaxDistance;
	if (400.f < fDist)
	{
		Destroy();
		return;
	}

	SetPos(vPos);
}