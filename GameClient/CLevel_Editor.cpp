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

void ButtonCallBackFunc()
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);

	if (nullptr == pEditorLevel)
		return;
}






CLevel_Editor::CLevel_Editor()
	: m_EditTile(nullptr)
	, m_TestPlatform(nullptr)
	, m_Type(MAP_TYPE::PLATFORM)
	, m_CurImg(nullptr)
	, m_BackGround(nullptr)
{
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::begin()
{
	m_CurImg = CAssetMgr::GetInst()->FindTexture(L"VOLCANO_01");
}

void CLevel_Editor::tick()
{

	if (KEY_TAP(KEY::_0))
	{
		m_BackGround = new CStage01;
		m_BackGround->SetPos(Vec2(0.f, 0.f));
		AddObject(LAYER_TYPE::BACKGROUND, m_BackGround);
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

	if (MAP_TYPE::PLATFORM == m_Type)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			m_TestPlatform = new CPlatform;
			m_Info.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			m_TestInfo.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			m_TestPlatform->SetPos(m_TestInfo.StartPos);
			m_TestPlatform->SetName(L"Test");
			AddObject(LAYER_TYPE::PLATFORM, m_TestPlatform);
		}

		else if (KEY_PRESSED(KEY::LBTN))
		{
			m_TestInfo.EndPos = CCamera::GetInst()->GetRenderPos(CKeyMgr::GetInst()->GetMousePos());
			m_TestPlatform->SetScale(m_TestInfo.EndPos);
		}

		else if (KEY_RELEASED(KEY::LBTN))
		{
			m_TestPlatform->Destroy();
			m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			float x = (m_Info.StartPos.x + m_Info.EndPos.x) * 0.5f;
			float y = (m_Info.StartPos.y + m_Info.EndPos.y) * 0.5f;
			float width = fabs(m_Info.EndPos.x - m_Info.StartPos.x);
			float height = fabs(m_Info.EndPos.y - m_Info.StartPos.y);
			m_Platform = new CPlatform(Vec2(x, y), Vec2(width, height));
			m_vecEditPlat.push_back(m_Platform);
			AddObject(LAYER_TYPE::PLATFORM, m_Platform);
		}
	}
	
	else if (MAP_TYPE::LINE == m_Type)
	{
		if (KEY_TAP(KEY::LBTN))
		{
			Vec2 vStartPos = CCamera::GetInst()->GetRenderPos(CKeyMgr::GetInst()->GetMousePos());
			m_Info.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			m_TestLine = new CLine;
			m_TestLine->SetPos(vStartPos);
			m_TestLine->SetName(L"Test");
			AddObject(LAYER_TYPE::LINE, m_TestLine);
		}

		else if (KEY_PRESSED(KEY::LBTN))
		{
			Vec2 vEndPos = CCamera::GetInst()->GetRenderPos(CKeyMgr::GetInst()->GetMousePos());
			m_TestLine->SetScale(vEndPos);
		}

		else if (KEY_RELEASED(KEY::LBTN))
		{
			m_TestLine->Destroy();
			m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			m_Line = new CLine(m_Info.StartPos, m_Info.EndPos);
			m_vecEditLine.push_back(m_Line);
			AddObject(LAYER_TYPE::LINE, m_Line);
		}
	}
	 
	if (KEY_TAP(KEY::T))
	{
		SaveToPlatformFile(L"platform\\platform.plat");
		SaveToLineFile(L"line\\line.dat");
	}

	else if (KEY_TAP(KEY::Y))
	{
		m_vecEditPlat.clear();
		LoadFromPlatform(L"platform\\platform.plat");
		LoadFromLine(L"line\\line.dat");
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CLevel_Editor::Enter()
{
	CCamera::GetInst()->SetOwner(nullptr);
}

void CLevel_Editor::Exit()
{
	DeleteAllObjects();
	m_vecEditPlat.clear();
}

void CLevel_Editor::SaveToPlatformFile(const wstring& _strRelativePath)
{
	wstring strPath = CPathMgr::GetInst()->GetContehtPath();
	strPath += _strRelativePath;

	FILE* pFile = nullptr;
	
	_wfopen_s(&pFile, strPath.c_str(), L"wb");
	
	size_t len = m_vecEditPlat.size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_vecEditPlat.size(); ++i)
	{
		Vec2 vPos = m_vecEditPlat[i]->GetPos();
		Vec2 vScale = m_vecEditPlat[i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}

void CLevel_Editor::SaveToLineFile(const wstring& _strRelativePath)
{
	wstring strPath = CPathMgr::GetInst()->GetContehtPath();
	strPath += _strRelativePath;
	
	FILE* pFile = nullptr;
	
	_wfopen_s(&pFile, strPath.c_str(), L"wb");
	
	size_t len = m_vecEditLine.size();
	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_vecEditLine.size(); ++i)
	{
		Vec2 vStartPos = m_vecEditLine[i]->GetPos();
		Vec2 vEndPos = m_vecEditLine[i]->GetScale();

		fwrite(&vStartPos, sizeof(Vec2), 1, pFile);
		fwrite(&vEndPos, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
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