#include "pch.h"
#include "CTrap_Eruption.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CTrap_Eruption::CTrap_Eruption()
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Time(0.f)
	, m_bActive(true)
{
}

CTrap_Eruption::CTrap_Eruption(Vec2 _Pos, OBJ_ID _ID)
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_Time(0.f)
	, m_bActive(true)
{
	// Info
	SetPos(_Pos);
	SetScale(10.f, 10.f);
	SetID(_ID);

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animator
	m_Animator->LoadAnimation(L"animation\\trap\\eruption\\ERUPTION.anim");

	m_Animator->Play(L"ERUPTION", false);
}

CTrap_Eruption::~CTrap_Eruption()
{
}

void CTrap_Eruption::tick()
{
	CObj::tick();
	
	if (m_Animator->GetCurAnim()->IsFinish())
	{
		m_bActive = false;
		m_Time += DT;
	}

	if (1.f < m_Time)
	{
		m_Animator->Play(L"ERUPTION", false);
		m_Time = 0.f;
		m_bActive = true;
	}
	
	if (m_bActive)
	{

		if (0 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(0.f, -30.f));
			m_Collider->SetScale(Vec2(70.f, 70.f));
		}

		else if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-20.f, -40.f));
			m_Collider->SetScale(Vec2(80.f,100.f));
		}

		else if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-60.f, -60.f));
			m_Collider->SetScale(Vec2(100.f,100.f));
		}
		else if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-100.f,-120.f));
			m_Collider->SetScale(Vec2(150.f, 100.f));
		}
		else if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-120.f, -140.f));
			m_Collider->SetScale(Vec2(170.f,60.f));
		}
		else if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-190.f, -140.f));
			m_Collider->SetScale(Vec2(240.f,100.f));
		}
		else if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-360.f, -35.f));
			m_Collider->SetScale(Vec2(80.f,80.f));
		}
		else if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(0.f,0.f));
			m_Collider->SetScale(Vec2(0.f,0.f));
		}
	}
}