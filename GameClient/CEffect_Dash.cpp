#include "pch.h"
#include "CEffect_Dash.h"
#include "CAnimator.h"
#include "CAnimation.h"

CEffect_Dash::CEffect_Dash(CObj* _Owner, Vec2 _Pos, Vec2 _Scale)
	: m_Owner(_Owner)
{
	// Info
	SetPos(_Pos);
	SetScale(_Scale);

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	
	// Animation
	m_Animator->LoadAnimation(L"animation\\player\\effect\\right\\EFFECT_DASH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\effect\\left\\EFFECT_DASH_LEFT.anim");

	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		m_Animator->Play(L"EFFECT_DASH_RIGHT", false);
	}

	else if (DIRECTION::LEFT == m_Owner->GetDirection())
	{
		m_Animator->Play(L"EFFECT_DASH_LEFT", false);
	}
}

CEffect_Dash::~CEffect_Dash()
{
}

void CEffect_Dash::tick()
{
	CObj::tick();

	if (m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
}
