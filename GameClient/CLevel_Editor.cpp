#include "pch.h"
#include "CLevel_Editor.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CPathMgr.h"
#include "CPlatform.h"
#include "CCollider.h"

CLevel_Editor::CLevel_Editor()
	: m_EditTile(nullptr)
	, m_Platform(nullptr)
{
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::begin()
{
}

void CLevel_Editor::tick()
{
	//if (KEY_TAP(KEY::LBTN))
	//{
	//	m_EditTile->Clicked(CKeyMgr::GetInst()->GetMousePos());
	//}
	//
	//else if (KEY_TAP(KEY::T))
	//{
	//	m_EditTile->SaveToFile(L"tile\\TestTile.tile");
	//}
	//
	//else if (KEY_TAP(KEY::Y))
	//{
	//	m_EditTile->LoadFromFile(L"tile\\TestTile.tile");
	//}

	if(KEY_TAP(KEY::LBTN))
	{
		m_Info.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		//m_Info.StartPos = CKeyMgr::GetInst()->GetMousePos();
	}
	
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		//m_Info.EndPos = CKeyMgr::GetInst()->GetMousePos();
		Rectangle(DC, (int)m_Info.StartPos.x, (int)m_Info.StartPos.y,
					  (int)m_Info.EndPos.x, (int)m_Info.EndPos.y);
	}
	
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_Info.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		float x = (m_Info.StartPos.x + m_Info.EndPos.x) * 0.5f;
		float y = (m_Info.StartPos.y + m_Info.EndPos.y) * 0.5f;
		float width = fabs(m_Info.EndPos.x - m_Info.StartPos.x);
		float height = fabs(m_Info.EndPos.y - m_Info.StartPos.y);
		m_Platform = new CPlatform(Vec2(x,y), Vec2(width,height));
		m_vecEditPlat.push_back(m_Platform);
		AddObject(LAYER_TYPE::PLATFORM, m_Platform);
	}
	 
	else if (KEY_TAP(KEY::T))
	{
		SaveToFile(L"platform\\platform.plat");
	}

	else if (KEY_TAP(KEY::Y))
	{
		m_vecEditPlat.clear();
		LoadFromFile(L"platform\\platform.plat");
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void CLevel_Editor::Enter()
{
	//m_EditTile = new CTile;
	//m_EditTile->SetPos(Vec2(0.f, 0.f));
	//
	//m_EditTile->SetRowCol(10, 10);
	//m_EditTile->SetAtlasTex(CAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));
	
	//m_EditPlat = new CPlatform;
	
	//AddObject(LAYER_TYPE::TILE, m_EditTile);
	//AddObject(LAYER_TYPE::PLATFORM, m_EditPlat);
}

void CLevel_Editor::Exit()
{
	DeleteAllObjects();
	m_vecEditPlat.clear();
}

void CLevel_Editor::SaveToFile(const wstring& _strRelativePath)
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

void CLevel_Editor::LoadFromFile(const wstring& _strRelativePath)
{
	wstring strPath = CPathMgr::GetInst()->GetContehtPath();
	strPath += _strRelativePath;
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"rb");

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);
		m_Platform = new CPlatform(vPos, vScale);
		m_vecEditPlat.push_back(m_Platform);
		AddObject(LAYER_TYPE::PLATFORM, m_vecEditPlat[i]);
	}
	
	fclose(pFile);
}