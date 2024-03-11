#include "pch.h"
#include "CTile.h"
#include "CTileMap.h"
#include "CPathMgr.h"

CTile::CTile()
{
	m_TileMap = (CTileMap*)AddComponent(new CTileMap);
}

CTile::~CTile()
{
}

void CTile::begin()
{
}

void CTile::tick()
{
}

void CTile::render()
{
	m_TileMap->render();
}

void CTile::SetRow(UINT _Row)
{
	m_TileMap->SetRow(_Row);
}

void CTile::SetCol(UINT _Col)
{
	m_TileMap->SetCol(_Col);
}

void CTile::SetRowCol(UINT _Row, UINT _Col)
{
	m_TileMap->SetRowCol(_Row, _Col);
}

void CTile::SetAtlasTex(CTexture* _Atlas)
{
	m_TileMap->SetAtlasTex(_Atlas);
}

void CTile::Clicked(Vec2 _MousePos)
{
	m_TileMap->Clicked(_MousePos);
}

void CTile::SaveToFile(const wstring& _RelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();
	strFilePath += _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"wb");

	// 타일의 위치
	Vec2 vPos = GetPos();
	fwrite(&vPos, sizeof(Vec2), 1, File);

	m_TileMap->SaveToFile(File);

	fclose(File);
}

void CTile::LoadFromFile(const wstring& _RelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();
	strFilePath += _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"rb");

	Vec2 vPos;
	fread(&vPos, sizeof(Vec2), 1, File);
	SetPos(vPos);

	m_TileMap->LoadFromFile(File);

	fclose(File);
}
