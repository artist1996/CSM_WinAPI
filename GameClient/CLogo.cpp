#include "pch.h"
#include "CLogo.h"
#include "CTexture.h"
#include "CAnimator.h"
#include "CAnimation.h"

CLogo::CLogo()
	: m_Animator(nullptr)
{
	SetName(L"Logo");
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_Animator->LoadAnimation(L"animation\\title\\TITLE.anim");
	m_Animator->Play(L"TITLE", true);
}

CLogo::~CLogo()
{
}

void CLogo::tick()
{
	CObj::tick();

}

void CLogo::render()
{
	CObj::render();
}