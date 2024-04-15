#include "pch.h"
#include "CEffect_Kick.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAnimator.h"
#include "CAnimation.h"

CEffect_Kick::CEffect_Kick()
	: m_Owner(nullptr)
	, m_Animator(nullptr)
	, m_Play(false)
{
	SetName(L"EFFECT_KICK");

	m_Owner = CLevelMgr::GetInst()->FindObjectByName(L"ZERO");
	
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	m_Animator->LoadAnimation(L"animation\\player\\effect\\EFFECT_KICK.anim");
}

CEffect_Kick::~CEffect_Kick()
{
}

void CEffect_Kick::Play(const wstring& _strName, bool _Play)
{
	m_Animator->Play(_strName, _Play);

	m_Play = true;
}

void CEffect_Kick::tick()
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

void CEffect_Kick::render()
{
	if (m_Play)
		m_Animator->render();
}