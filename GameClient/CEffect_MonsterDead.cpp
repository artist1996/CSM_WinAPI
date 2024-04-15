#include "pch.h"
#include "CEffect_MonsterDead.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CSound.h"

CEffect_MonsterDead::CEffect_MonsterDead()
	: m_Owner(nullptr)
	, m_Animator(nullptr)
	, m_pSound(nullptr)
{
}

CEffect_MonsterDead::CEffect_MonsterDead(CObj* _Owner)
	: m_Owner(_Owner)
	, m_Animator(nullptr)
	, m_pSound(nullptr)
{
	// Info
	SetPos(m_Owner->GetPos());
	SetScale(Vec2(10.f, 10.f));
	// Component

	m_pSound = CAssetMgr::GetInst()->LoadSound(L"BOMB", L"sound\\bomb\\Bomb.wav");

	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animation
	m_Animator->LoadAnimation(L"animation\\monster\\Dead.anim");

	m_Animator->Play(L"Dead", false);
	m_pSound->Play();
}

CEffect_MonsterDead::~CEffect_MonsterDead()
{
}

void CEffect_MonsterDead::tick()
{
	CObj::tick();

	if (m_Animator->GetCurAnim()->IsFinish())
		Destroy();
}