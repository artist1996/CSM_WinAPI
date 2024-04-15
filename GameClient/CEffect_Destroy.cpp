#include "pch.h"
#include "CEffect_Destroy.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CSound.h"


CEffect_Destroy::CEffect_Destroy()
	: m_Owner(nullptr)
	, m_Animator(nullptr)
{
}

CEffect_Destroy::CEffect_Destroy(CObj* _Owner)
	: m_Owner(_Owner)
	, m_Animator(nullptr)
{
	// Info
	int Rand = rand() % 2;
	
	if (0 == Rand)
	{
		float fRandX = rand() % 100;
		float fRandY = rand() % 100;

		float x = m_Owner->GetPos().x - fRandX;
		float y = m_Owner->GetPos().y - fRandY;
		SetPos(x, y);
	}

	else if (1 == Rand)
	{
		float fRandX = rand() % 100;
		float fRandY = rand() % 100;

		float x = m_Owner->GetPos().x + fRandX;
		float y = m_Owner->GetPos().y + fRandY;
		SetPos(x, y);
	}

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animator
	m_Animator->LoadAnimation(L"animation\\monster\\Dead.anim");
	// Animation
	m_Animator->Play(L"Dead", false);
}

CEffect_Destroy::~CEffect_Destroy()
{
}

void CEffect_Destroy::tick()
{
	if (m_Animator->GetCurAnim()->IsFinish())
		Destroy();
}

void CEffect_Destroy::render()
{
	m_Animator->render();
}
