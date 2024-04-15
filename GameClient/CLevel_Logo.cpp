#include "pch.h"
#include "CLevel_Logo.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLogo.h"

CLevel_Logo::CLevel_Logo()
	: m_Logo(nullptr)
	, m_Img(nullptr)
	, m_Count(0)
{
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"GameStart", L"texture\\GameStart.png");
}

CLevel_Logo::~CLevel_Logo()
{
}


void CLevel_Logo::begin()
{
	CLevel::begin();
}

void CLevel_Logo::tick()
{
	CLevel::tick();

	if (0 > m_Count)
	{
		m_Count = 2;
	}
	
	else if (2 < m_Count)
	{
		m_Count = 0;
	}
	
	if (0 == m_Count)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"GameStart_Title", L"texture\\GameStart.png");
	}
	
	else if (1 == m_Count)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Continue_Title", L"texture\\Continue.png");
	}
	
	else if (2 == m_Count)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Option_Title", L"texture\\Option.png");
	}
	
	if (KEY_TAP(KEY::DOWN))
	{
		++m_Count;	
	}
	
	else if (KEY_TAP(KEY::UP))
	{
		--m_Count;
	}
	
	if (KEY_TAP(KEY::ENTER))
	{
		switch (m_Count)
		{
		case 0:
			ChangeLevel(LEVEL_TYPE::SELECT);
			break;
		case 1:
			ChangeLevel(LEVEL_TYPE::EDITOR);
			break;
		case 2:
			ChangeLevel(LEVEL_TYPE::TOOL);
			break;
		}
	}
}

void CLevel_Logo::render()
{
	CLevel::render();
	// 430 370
	BLENDFUNCTION bf = {};
	
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;
	
	AlphaBlend(DC, 280
				 , 300
				, m_Img->GetWidth(), m_Img->GetHeight()
				, m_Img->GetDC()
				, 0, 0
				, m_Img->GetWidth(), m_Img->GetHeight(), bf);
}

void CLevel_Logo::Enter()
{
	//CEngine::GetInst()->ChangeWindowSize(Vec2(800.f, 600.f), false);
	m_Logo = new CLogo;
	m_Logo->SetPos(Vec2(0.f, 0.f));

	CCamera::GetInst()->SetCameraLookAt(Vec2(400.f, 300.f));

	AddObject(LAYER_TYPE::BACKGROUND, m_Logo);
}

void CLevel_Logo::Exit()
{
	DeleteAllObjects();
}