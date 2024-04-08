#include "pch.h"
#include "CUI_Warning.h"

#include "CAnimator.h"
#include "CAnimation.h"

CUI_Warning::CUI_Warning()
	: m_Animator(nullptr)
	, m_Count(0)
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	m_Animator->LoadAnimation(L"animation\\warning\\WARNING_ENTER.anim");
	m_Animator->LoadAnimation(L"animation\\warning\\WARNING.anim");
	
	m_Animator->Play(L"WARNING_ENTER", false);
}

CUI_Warning::~CUI_Warning()
{
}


void CUI_Warning::tick_ui()
{
	if (L"WARNING_ENTER" == m_Animator->GetCurAnim()->GetName() && m_Animator->GetCurAnim()->IsFinish())
	{
		m_Animator->Play(L"WARNING", true);
	}
	
	if (L"WARNING" == m_Animator->GetCurAnim()->GetName() && m_Animator->GetCurAnim()->IsFinish())
	{
		++m_Count;
	}
	
	if (6 <= m_Count && m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
}