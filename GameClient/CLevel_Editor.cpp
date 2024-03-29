#include "pch.h"
#include "CLevel_Editor.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CPathMgr.h"

#include "CTile.h"
#include "CPlatform.h"
#include "CLine.h"
#include "CCollider.h"
#include "CTexture.h"
#include "CBackGround.h"
#include "CStage01.h"
#include "CPanel.h"
#include "CButton.h"
#include "CEditorUI.h"
#include "CMonster.h"

void ButtonCallBackFunc()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);

	if (nullptr == pEditorLevel)
		return;
}

CLevel_Editor::CLevel_Editor()
	: m_EditTile(nullptr)
	, m_UI(nullptr)
	, m_CurImg(nullptr)
	, m_BackGround(nullptr)
	, m_Type(MAP_TYPE::PLATFORM)
{
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::begin()
{
	CLevel::begin();
	m_CurImg = CAssetMgr::GetInst()->FindTexture(L"VOLCANO_01");
}

void CLevel_Editor::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::_1))
	{
		m_BackGround = new CStage01;
		m_BackGround->SetPos(Vec2(0.f, 0.f));
		AddObject(LAYER_TYPE::BACKGROUND, m_BackGround);
		SetName(L"Stage01");
	}

	else if (KEY_TAP(KEY::_2))
	{
		//m_BackGround = new CStage02;
		SetName(L"Stage02");
	}

	if (KEY_TAP(KEY::_9))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"radien_editor", L"texture\\raiden_editor.png"));
	}

	if (KEY_TAP(KEY::_8))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"gigadeath_editor", L"texture\\gigadeath_editor.png"));
	}

	if (KEY_TAP(KEY::_7))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"mettool_editor", L"texture\\mettool_editor.png"));
	}

	if(KEY_TAP(KEY::_6))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"batton_editor", L"texture\\batton_editor.png"));
	}

	if (KEY_TAP(KEY::P))
	{
		SetType(MAP_TYPE::PLATFORM);
		ResetInfo();
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"PLATFORM", L"Type", MB_OK);
	}

	else if (KEY_TAP(KEY::L))
	{
		SetType(MAP_TYPE::LINE);
		ResetInfo();
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"LINE", L"Type", MB_OK);
	}

	else if (KEY_TAP(KEY::M))
	{
		SetType(MAP_TYPE::MONSTER);
		ResetInfo();
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"MONSERT", L"Type", MB_OK);
	}

	if (MAP_TYPE::PLATFORM == m_Type)
	{
		Platform();
	}
	
	else if (MAP_TYPE::LINE == m_Type)
	{
		Line();
	}

	else if (MAP_TYPE::MONSTER == m_Type)
	{
		Monster();
	}
	 
	if (KEY_TAP(KEY::T))
	{
		SavePlatform(L"platform\\platform.dat");
		SaveLine(L"line\\line.dat");
		SaveMonster(L"monster\\monster.dat");
		SaveTrap(L"trap\\trap.dat");
	}

	else if (KEY_TAP(KEY::Y))
	{
		LoadPlatform(L"platform\\platform.dat");
		LoadLine(L"line\\line.dat");
		LoadMonster(L"monster\\monster.dat");
		LoadTrap(L"trap\\trap.dat");
	}

	if (KEY_TAP(KEY::_5))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CLevel_Editor::Enter()
{
	CCamera::GetInst()->SetOwner(nullptr);
	m_UI = new CEditorUI;//(Vec2(CEngine::GetInst()->GetResolution().x - 200.f, 0.f), Vec2(400.f, 200.f));
	m_UI->SetScale(Vec2(150.f, 150.f));
	m_UI->SetPos(CEngine::GetInst()->GetResolution().x - 150.f, 0.f);
	AddObject(LAYER_TYPE::UI, m_UI);
}

void CLevel_Editor::Exit()
{
	DeleteAllObjects();
}

void CLevel_Editor::Platform()
{
	if (KEY_TAP(KEY::LBTN))
	{
		m_tInfo.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	}

	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_tInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	}

	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_tInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		float x = (m_tInfo.StartPos.x + m_tInfo.EndPos.x) * 0.5f;
		float y = (m_tInfo.StartPos.y + m_tInfo.EndPos.y) * 0.5f;
		float width = m_tInfo.EndPos.x - m_tInfo.StartPos.x;
		float height = m_tInfo.EndPos.y - m_tInfo.StartPos.y;
		CPlatform* pPlatform = new CPlatform(Vec2(x, y), Vec2(width, height));
		AddObject(LAYER_TYPE::PLATFORM, pPlatform);
		memset(&m_tInfo, 0, sizeof(tInfo));
	}
}

void CLevel_Editor::Line()
{
	if (KEY_TAP(KEY::LBTN))
	{
		m_tInfo.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	}
	
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_tInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	}

	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_tInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		CLine* pLine = new CLine(m_tInfo.StartPos, m_tInfo.EndPos);
		AddObject(LAYER_TYPE::LINE, pLine);
		memset(&m_tInfo, 0, sizeof(tInfo));
	}
}

void CLevel_Editor::Monster()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		CMonster* pMonster = new CMonster;
		pMonster->SetPos(vPos);
		pMonster->SetScale(100.f, 100.f);
		AddObject(LAYER_TYPE::MONSTER, pMonster);
	}
}

void CLevel_Editor::Trap()
{
}

void CLevel_Editor::CreateUI()
{
	// 화면 해상도
	Vec2 vResol = CEngine::GetInst()->GetResolution();

	CPanel* pPanelUI = new CPanel;
	
	pPanelUI->SetScale(Vec2(400.f, 500.f));
	pPanelUI->SetPos(Vec2(vResol.x - (pPanelUI->GetScale().x + 10.f), 10.f));
	
	CButton* pUI = new CButton;
	
	pUI->SetCallBack(&ButtonCallBackFunc);
}

void CLevel_Editor::render()
{
	CLevel::render();

	if (m_Type == MAP_TYPE::PLATFORM)
	{
		USE_PEN(DC, PEN_TYPE::PEN_GREEN);
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

		Vec2 Start = CCamera::GetInst()->GetRenderPos(m_tInfo.StartPos);
		Vec2 End = CCamera::GetInst()->GetRenderPos(m_tInfo.EndPos);

		Rectangle(DC, (int)Start.x, (int)Start.y, (int)End.x, (int)End.y);
	}

	if (m_Type == MAP_TYPE::LINE)
	{
		USE_PEN(DC, PEN_TYPE::PEN_GREEN);
		
		Vec2 Start = CCamera::GetInst()->GetRenderPos(m_tInfo.StartPos);
		Vec2 End = CCamera::GetInst()->GetRenderPos(m_tInfo.EndPos);

		MoveToEx(DC, (int)Start.x, (int)Start.y, nullptr);
		LineTo(DC, (int)End.x, (int)End.y);
	}
}