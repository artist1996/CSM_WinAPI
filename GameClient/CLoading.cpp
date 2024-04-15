#include "pch.h"
#include "CLoading.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAnimator.h"

CLoading::CLoading()
	: m_Animator(nullptr)
{
	//SetPos(Vec2(400.f, 600.f));

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animator
	m_Animator->LoadAnimation(L"animation\\loading\\Loading_Area1.anim");
	m_Animator->LoadAnimation(L"animation\\loading\\Loading_Area2.anim");

	if (L"SELECT" == CLevelMgr::GetInst()->GetPrevLevel()->GetName())
	{
		SetPos(Vec2(400.f, 600.f));
		m_Animator->Play(L"Loading_Area1", true);
	}

	else if (L"Stage01" == CLevelMgr::GetInst()->GetPrevLevel()->GetName())
	{
		SetPos(Vec2(400.f, 600.f));
		m_Animator->Play(L"Loading_Area2", true);
	}
}

CLoading::~CLoading()
{
}

void CLoading::tick()
{
	CObj::tick();
}

void CLoading::render()
{
	CObj::render();
	m_Animator->render();
}
