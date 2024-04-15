#include "pch.h"
#include "CLevel_Select.h"
#include "CLevelMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

#include "CBackGround.h"
#include "CSelect.h"

#include "CUI.h"
#include "CUI_Select.h"
#include "CUI_Message.h"


#include "CDummy_Select.h"

CLevel_Select::CLevel_Select()
	: m_bX(true)
	, m_bZero(false)
	, m_UI(nullptr)
	, m_Zero(nullptr)
	, m_X(nullptr)
	, m_bChange(false)
	, m_Sound(nullptr)
	, m_Sound2(nullptr)
	, m_Sound3(nullptr)
{
	SetName(L"SELECT");
}

CLevel_Select::~CLevel_Select()
{
}

void CLevel_Select::begin()
{
	CLevel::begin();

	m_Sound = CAssetMgr::GetInst()->LoadSound(L"SELECT_BGM", L"sound\\level\\Select.wav");
	CSoundMgr::GetInst()->RegisterToBGM(m_Sound);
	m_Sound->SetVolume(20.f);
	m_Sound->PlayToBGM(true);

	m_Sound2 = CAssetMgr::GetInst()->LoadSound(L"SELECT", L"sound\\select\\SELECT.wav");
	m_Sound3 = CAssetMgr::GetInst()->LoadSound(L"SELECT02", L"sound\\select\\SELECT02.wav");
}

void CLevel_Select::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::RIGHT))
	{
		m_bX = false;
		if (m_bZero)
		{
			return;
		}
		m_bZero = true;
		m_Sound2->Play(false);
		m_UI->SetZero(true);
		m_UI->Play(L"SELECT_ZERO");
		m_X->Play(L"IDLE", true);
		m_Zero->Play(L"ATTACK01_LEFT_DUMMY", true);
	}

	else if (KEY_TAP(KEY::LEFT))
	{
		m_bZero = false;
		if (m_bX)
		{
			return;
		}
		
		m_Sound2->Play(false);
		m_Zero->Play(L"IDLE_LEFT", true);
		m_UI->SetX(true);
		m_UI->Play(L"SELECT_X");
		m_bX = true;
		m_X->Play(L"SHOOT", true);
	}

	if (KEY_TAP(KEY::ENTER))
	{
		m_bChange = true;
		m_Sound3->Play(false);
		m_Zero->Play(L"VICTORY_LEFT_DUMMY", false);
		m_X->Play(L"RECALL", false);
	}

	if (m_bChange)
	{
		m_Time += DT;

		if (2.f <= m_Time)
		{
			ChangeLevel(LEVEL_TYPE::LOADING);
		}
	}
}

void CLevel_Select::Enter()
{
	CBackGround* pBackGround = new CSelect;
	m_UI = new CUI_Select;
	m_Zero = new CDummy_Select(Vec2(740.f, 490.f), 1);
	m_X = new CDummy_Select(Vec2(50.f, 490.f), 0);

	CUI_Message* pUI = new CUI_Message(Vec2(-400.f, 0.f), 0);
	AddObject(LAYER_TYPE::UI, pUI);
	pUI = new CUI_Message(Vec2(800.f, 500.f), 1);
	AddObject(LAYER_TYPE::UI, pUI);
	
	AddObject(LAYER_TYPE::DUMMY, m_Zero);
	AddObject(LAYER_TYPE::DUMMY, m_X);
	AddObject(LAYER_TYPE::BACKGROUND, pBackGround);
	AddObject(LAYER_TYPE::UI, m_UI);

	CLevelMgr::GetInst()->SetPrevLevel(this);
}

void CLevel_Select::Exit()
{
	CSoundMgr::GetInst()->RegisterToBGM(nullptr);
	DeleteAllObjects();
}