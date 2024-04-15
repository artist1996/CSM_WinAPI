#include "pch.h"
#include "CUI_Select.h"

#include "CAnimator.h"
#include "CAnimation.h"

CUI_Select::CUI_Select()
{
	SetPos(Vec2(210.f, 490.f));
	

	m_Animator = (CAnimator*)AddComponent(new CAnimator);


	m_Animator->LoadAnimation(L"animation\\select\\SELECT_X.anim");
	m_Animator->LoadAnimation(L"animation\\select\\SELECT_ZERO.anim");

	m_Animator->Play(L"SELECT_X", true);
}

CUI_Select::~CUI_Select()
{
}

void CUI_Select::Play(const wstring& _strName)
{
	m_Animator->Play(_strName, true);
}

void CUI_Select::tick_ui()
{
}