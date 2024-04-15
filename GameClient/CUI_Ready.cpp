#include "pch.h"
#include "CUI_Ready.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CFSM.h"
#include "CSoundMgr.h"

#include "CSound.h"

CUI_Ready::CUI_Ready()
	: m_Animator(nullptr)
	, m_Sound(nullptr)
	, m_bPlay(false)
	, m_Time(0.f)
{
}

CUI_Ready::CUI_Ready(Vec2 _Pos)
	: m_Animator(nullptr)
	, m_Sound(nullptr)
	, m_bPlay(true)
	, m_Time(0.f)
{
	// Info
	SetPos(_Pos);

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Animator
	
	//CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"READY", L"texture\\Ready.png");
	//m_Animator->CreateAnimation(L"READY", pTex, Vec2(0.f, 0.f), Vec2(400.f, 0.f), 12, 1);
	//m_Animator->FindAnimation(L"READY")->Save(L"animation\\ready\\Ready");
	m_Animator->LoadAnimation(L"animation\\ready\\READY.anim");

	// Sound
	m_Sound = CAssetMgr::GetInst()->LoadSound(L"READY", L"sound\\level\\READY.wav");
	m_Sound->SetVolume(30.f);
	m_Sound->Play(false);
}

CUI_Ready::~CUI_Ready()
{
}

void CUI_Ready::tick_ui()
{
	if (m_bPlay)
	{
		m_Time += DT;
	}

	if (0.5f <= m_Time)
	{
		m_Animator->Play(L"READY", false);
		m_bPlay = false;
		m_Time = 0.f;
	}
	
	if (nullptr != m_Animator->GetCurAnim() && m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
		CLevelMgr::GetInst()->FindObjectByName(L"ZERO")->GetComponent<CFSM>()->ChangeState(L"START");
	}
}