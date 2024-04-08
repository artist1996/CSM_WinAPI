#include "pch.h"
#include "CLevel_Editor.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CPathMgr.h"

#include "CTile.h"
#include "CPlatform.h"
#include "CLine.h"
#include "CCollider.h"
#include "CTexture.h"

#include "CBackGround.h"
#include "CStage01.h"
#include "CStage02.h"

#include "CPanel.h"
#include "CButton.h"
#include "CEditorUI.h"
#include "CMonster.h"
#include "CMonster_Mettool.h"
#include "CMonster_Raiden.h"
#include "CMonster_GigaDeath.h"
#include "CMonster_Batton.h"

#include "CTrap_Meteor.h"

#include "CEditor_RenderDummy.h"

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
	, m_ID(OBJ_ID::END)
{
	SetName(L"Editor");
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
		SetSaveType(SAVE_TYPE::STAGE01);
	}

	else if (KEY_TAP(KEY::_2))
	{
		m_BackGround = new CStage02;
		m_BackGround->SetPos(Vec2(0.f, 0.f));
		AddObject(LAYER_TYPE::BACKGROUND, m_BackGround);
		SetSaveType(SAVE_TYPE::STAGE02);			
	}

	if (KEY_TAP(KEY::_9))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		m_ID = OBJ_ID::RAIDEN;
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"radien_editor", L"texture\\raiden_editor.png"));
	}

	if (KEY_TAP(KEY::_8))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		m_ID = OBJ_ID::GIGADEATH;
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"gigadeath_editor", L"texture\\gigadeath_editor.png"));
	}

	if (KEY_TAP(KEY::_7))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		m_ID = OBJ_ID::METTOOL;
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"mettool_editor", L"texture\\mettool_editor.png"));
	}

	if(KEY_TAP(KEY::_6))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		m_ID = OBJ_ID::BATTON;
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"batton_editor", L"texture\\batton_editor.png"));
	}

	if (KEY_TAP(KEY::_5))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		m_ID = OBJ_ID::METEOR_UP;
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"meteorup_editor", L"texture\\meteorup_editor.png"));
	}

	if (KEY_TAP(KEY::_4))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		m_ID = OBJ_ID::METEOR_DOWN;
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"meteordown_editor", L"texture\\meteordown_editor.png"));
	}

	if (KEY_TAP(KEY::_3))
	{
		CEditorUI* pUI = dynamic_cast<CEditorUI*>(m_UI);
		m_ID = OBJ_ID::ERUPTION;
		pUI->SetImg(CAssetMgr::GetInst()->LoadTexture(L"eruption_editor", L"texture\\eruption_editor.png"));
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
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"MONSTER", L"Type", MB_OK);
	}

	else if (KEY_TAP(KEY::N))
	{
		SetType(MAP_TYPE::TRAP);
		ResetInfo();
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"TRAP", L"Type", MB_OK);
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

	else if (MAP_TYPE::TRAP == m_Type)
	{
		Trap();
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

	if (KEY_TAP(KEY::C))
	{
		ChangeLevel(LEVEL_TYPE::LOGO_START);
	}
}

void CLevel_Editor::Enter()
{
	CCamera::GetInst()->SetOwner(nullptr);
	m_UI = new CEditorUI;
	m_UI->SetScale(Vec2(150.f, 150.f));
	m_UI->SetPos(CEngine::GetInst()->GetResolution().x - 150.f, 0.f);
	AddObject(LAYER_TYPE::UI, m_UI);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLATFORM, LAYER_TYPE::MONSTER);
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
		float width = fabs(m_tInfo.EndPos.x - m_tInfo.StartPos.x);
		float height = fabs(m_tInfo.EndPos.y - m_tInfo.StartPos.y);
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
		
		if (OBJ_ID::METTOOL == m_ID)
		{
			CEditor_RenderDummy* pDummy = new CEditor_RenderDummy(vPos, Vec2(50.f, 50.f), OBJ_ID::METTOOL, 1, 200.f);
			AddObject(LAYER_TYPE::MONSTER, pDummy);
			return;
		}

		else if (OBJ_ID::RAIDEN == m_ID)
		{
			CEditor_RenderDummy* pMonster = new CEditor_RenderDummy(vPos, Vec2(150.f, 180.f), OBJ_ID::RAIDEN, 6, 200.f);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::GIGADEATH == m_ID)
		{
			CEditor_RenderDummy* pMonster = new CEditor_RenderDummy(vPos, Vec2(200.f, 180.f), OBJ_ID::GIGADEATH, 5, 200.f);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::BATTON == m_ID)
		{
			CEditor_RenderDummy* pMonster = new CEditor_RenderDummy(vPos, Vec2(50.f, 70.f), OBJ_ID::BATTON, 2, 200.f);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
			return;
		}
	}
}

void CLevel_Editor::Trap()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		
		if (OBJ_ID::METEOR_UP == m_ID)
		{
			CEditor_RenderDummy* pTrap = new CEditor_RenderDummy(vPos, Vec2(120.f,130.f), OBJ_ID::METEOR_UP, 3, 200.f);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}

		else if (OBJ_ID::METEOR_DOWN == m_ID)
		{
			CEditor_RenderDummy* pTrap = new CEditor_RenderDummy(vPos, Vec2(120.f, 130.f), OBJ_ID::METEOR_DOWN, 3, 200.f);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}
		
		else if (OBJ_ID::ERUPTION == m_ID)
		{
			CEditor_RenderDummy* pTrap = new CEditor_RenderDummy(vPos, Vec2(10.f, 10.f), OBJ_ID::ERUPTION, 0, 200.f);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}
	}
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