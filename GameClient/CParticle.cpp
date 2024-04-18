#include "pch.h"
#include "CParticle.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAnimator.h"
#include "CAnimation.h"

CParticle::CParticle()
	: m_Owner(nullptr)
	, m_Animator(nullptr)
	, m_Active(false)
	, m_Type(EFFECT_TYPE::END)
{
}

CParticle::CParticle(EFFECT_TYPE _Type)
	: m_Owner(nullptr)
	, m_Animator(nullptr)
	, m_Active(false)
	, m_Type(_Type)
{
	m_Owner = CLevelMgr::GetInst()->FindObjectByName(L"ZERO");

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animator
	//m_Animator->LoadAnimation();
}

CParticle::~CParticle()
{
}

void CParticle::tick()
{
}

void CParticle::render()
{
	if (m_Active)
		m_Animator->render();
}
