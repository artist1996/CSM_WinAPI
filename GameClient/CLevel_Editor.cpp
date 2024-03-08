#include "pch.h"
#include "CLevel_Editor.h"
#include "CKeyMgr.h"
#include "CTile.h"
#include "CPlatform.h"

CLevel_Editor::CLevel_Editor()
	: m_EditTile(nullptr)
	, m_EditPlat(nullptr)
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

	if(KEY_TAP(KEY::LBTN))
	{
		m_PlatInfo.StartPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	}

	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_PlatInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		Rectangle(DC, (int)m_PlatInfo.StartPos.x, (int)m_PlatInfo.StartPos.y, (int)m_PlatInfo.EndPos.x, (int)m_PlatInfo.EndPos.y);
	}
	
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_PlatInfo.EndPos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
		m_EditPlat = new CPlatform(m_PlatInfo.StartPos, m_PlatInfo.EndPos);
		SpawnObject(this, LAYER_TYPE::PLATFORM, m_EditPlat);
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
}