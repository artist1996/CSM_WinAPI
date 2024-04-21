#include "pch.h"
#include "CUI_Warning.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CFSM.h"

#include "CSoundMgr.h"
#include "CSound.h"


CUI_Warning::CUI_Warning()
	: m_Animator(nullptr)
	, m_Target(nullptr)
	, m_Count(0)
	, m_Sound(nullptr)
{
	SetName(L"WARNING_UI");

	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	m_Animator->LoadAnimation(L"animation\\warning\\WARNING_ENTER.anim");
	m_Animator->LoadAnimation(L"animation\\warning\\WARNING.anim");

	m_Sound = CAssetMgr::GetInst()->LoadSound(L"WARNING", L"sound\\level\\WARNING.wav");
	m_Sound->SetVolume(20.f);
	//m_Sound->Play(true);

	//CSoundMgr::GetInst()->RegisterToBGM(nullptr);
}

CUI_Warning::~CUI_Warning()
{
}


void CUI_Warning::tick_ui()
{
	if (nullptr != m_Animator->GetCurAnim())
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
			CFSM* pFSM = m_Target->GetComponent<CFSM>();
			pFSM->ChangeState(L"ENTER");
			m_Sound->Stop(true);
			Destroy();
		}
	}
}

void CUI_Warning::Play()
{
	m_Animator->Play(L"WARNING_ENTER", false);
	m_Sound->Play(true);

	CSoundMgr::GetInst()->RegisterToBGM(nullptr);
}
