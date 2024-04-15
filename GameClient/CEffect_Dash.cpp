#include "pch.h"
#include "CEffect_Dash.h"
#include "CAnimator.h"
#include "CAnimation.h"

CEffect_Dash::CEffect_Dash(CObj* _Owner, Vec2 _Pos, Vec2 _Scale)
	: m_Owner(_Owner)
	, m_Play(false)
	, m_Active(false)
{
	SetName(L"EFFECT_DASH");
	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	
	// Animation
	m_Animator->LoadAnimation(L"animation\\player\\effect\\right\\EFFECT_DASH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\effect\\left\\EFFECT_DASH_LEFT.anim");

	// Info
	SetPos(_Pos);
	SetScale(_Scale);
}

CEffect_Dash::~CEffect_Dash()
{
}

void CEffect_Dash::tick()
{
	CObj::tick();

	if (m_Play)
	{
		if (m_Animator->GetCurAnim()->IsFinish())
		{
			m_Play = false;
		}
	}
}

void CEffect_Dash::render()
{
	//CObj::render();
	
	if (m_Play)
		m_Animator->render();
}

void CEffect_Dash::Play(const wstring& _strName, bool _Play)
{
    m_Animator->Play(_strName, _Play);
	m_Active = true;
	m_Play = true;
}
