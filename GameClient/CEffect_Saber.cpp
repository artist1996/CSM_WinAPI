#include "pch.h"
#include "CEffect_Saber.h"

#include "CAnimator.h"
#include "CAnimation.h"

CEffect_Saber::CEffect_Saber()
	: m_Animator(nullptr)
	, m_Type(EFFECT_TYPE::END)
{
}

CEffect_Saber::CEffect_Saber(Vec2 _Pos, EFFECT_TYPE _Type)
	: m_Animator(nullptr)
	, m_Type(_Type)
{
	// Info
	SetPos(_Pos);

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	
	// Animator
	m_Animator->LoadAnimation(L"animation\\player\\effect\\SABER1.anim");
	m_Animator->LoadAnimation(L"animation\\player\\effect\\SABER2.anim");
	
	if (EFFECT_TYPE::EFFECT_ONE == m_Type)
	{
		m_Animator->Play(L"SABER1", false);
	}

	else if (EFFECT_TYPE::EFFECT_TWO == m_Type)
	{
		m_Animator->Play(L"SABER2", false);
	}
}

CEffect_Saber::~CEffect_Saber()
{
}

void CEffect_Saber::tick()
{
	CObj::tick();

	if (m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
}