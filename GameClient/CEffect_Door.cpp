#include "pch.h"
#include "CEffect_Door.h"

#include "CAnimator.h"
#include "CAnimation.h"

CEffect_Door::CEffect_Door()
	: m_Animator(nullptr)
{
}

CEffect_Door::CEffect_Door(Vec2 _Pos)
	: m_Animator(nullptr)
{
	// Info
	SetPos(_Pos);
	SetScale(Vec2(10.f, 10.f));

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animator
	m_Animator->LoadAnimation(L"animation\\Destroy.anim");

	// Animation
	m_Animator->Play(L"Destroy", false);
}

CEffect_Door::~CEffect_Door()
{
}

void CEffect_Door::tick()
{
	if (m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
}