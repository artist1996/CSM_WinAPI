#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CCollider.h"
#include "CPathMgr.h"
#include "CPlatform.h"
#include "CPlatform_Death.h"
#include "CLine.h"
#include "CMonster.h"
#include "CMonster_Mettool.h"
#include "CMonster_Raiden.h"
#include "CMonster_GigaDeath.h"
#include "CMonster_Batton.h"

#include "CTrap_Meteor.h"
#include "CTrap_Eruption.h"

#include "CEditor_RenderDummy.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		Safe_Del_Vec(m_arrObj[i]);
	}
}

void CLevel::begin()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->begin();
		}
	}
}

void CLevel::tick()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->tick();
		}
	}
}

void CLevel::finaltick()
{
	// 이전프레임 충돌체 등록 정보 Clear
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrCollider[i].clear();
	}	


	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finaltick();
		}
	}
}

void CLevel::render()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		vector<CObj*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrObj[i].erase(iter);
			}
			else
			{
				(*iter)->render();
				++iter;
			}			
		}
	}
}

void CLevel::AddObject(LAYER_TYPE _Layer, CObj* _Obj)
{
	m_arrObj[(UINT)_Layer].push_back(_Obj);
	_Obj->m_Type = _Layer;
}

void CLevel::RegisterCollider(CCollider* _Collider)
{
	LAYER_TYPE Layer = _Collider->GetOwner()->GetLayerType();
	m_arrCollider[(UINT)Layer].push_back(_Collider);
}

CObj* CLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		CObj* pFindObj = FindObjectByName((LAYER_TYPE)i, _Name);

		if (pFindObj)
		{
			return pFindObj;
		}
	}

	return nullptr;
}

CObj* CLevel::FindObjectByName(LAYER_TYPE _Type, const wstring& _Name)
{
	for (size_t i = 0; i < m_arrObj[(UINT)_Type].size(); ++i)
	{
		if (_Name == m_arrObj[(UINT)_Type][i]->GetName())
		{
			return m_arrObj[(UINT)_Type][i];
		}
	}

	return nullptr;
}

void CLevel::DeleteAllObjects()
{
	for (size_t i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		DeleteObjects((LAYER_TYPE)i);
	}

}

void CLevel::DeleteObjects(LAYER_TYPE _Type)
{
	// 해당 레이어 타입의 오브젝트만 삭제 해준다.
	vector<CObj*>& vecObj = m_arrObj[(UINT)_Type];

	//if (vecObj.empty())
	//	return;

	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		delete vecObj[i];
	}

	vecObj.clear();
}

void CLevel::pop_back(LAYER_TYPE _Type)
{
	if (m_arrObj[(UINT)_Type].empty())
		return;

	CObj* pObj = m_arrObj[(UINT)_Type].back();
	pObj->Destroy();
	m_arrObj[(UINT)_Type].pop_back();
}

void CLevel::SaveDeathPlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();
	if (SAVE_TYPE::STAGE01 == m_Save)
	{
		strFullPath += L"stage01\\";
	}

	else if (SAVE_TYPE::STAGE02 == m_Save)
	{
		strFullPath += L"stage02\\";
	}

	FILE* pFile = nullptr;

	strFullPath += _strRelativePath;


	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	size_t len = m_arrObj[(UINT)LAYER_TYPE::TILE].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"파일 개방 실패", L"Error", MB_OK);
		return;
	}

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::TILE].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::TILE][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::TILE][i]->GetScale();

		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}

void CLevel::SavePlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();
	if (SAVE_TYPE::STAGE01 == m_Save)
	{
		strFullPath += L"stage01\\";
	}

	else if (SAVE_TYPE::STAGE02 == m_Save)
	{
		strFullPath += L"stage02\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;
	
	
	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"파일 개방 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::PLATFORM].size();
	
	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::PLATFORM].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::PLATFORM][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::PLATFORM][i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}

void CLevel::SaveLine(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	if (SAVE_TYPE::STAGE01 == m_Save)
	{
		strFullPath += L"stage01\\";
	}

	else if (SAVE_TYPE::STAGE02 == m_Save)
	{
		strFullPath += L"stage02\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"파일 개방 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::LINE].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::LINE].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::LINE][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::LINE][i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}

void CLevel::SaveMonster(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	if (SAVE_TYPE::STAGE01 == m_Save)
	{
		strFullPath += L"stage01\\";
	}
	
	else if (SAVE_TYPE::STAGE02 == m_Save)
	{
		strFullPath += L"stage02\\";
	}
	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"파일 개방 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::MONSTER].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::MONSTER].size(); ++i)
	{
		OBJ_ID ID = dynamic_cast<CEditor_RenderDummy*>(m_arrObj[(UINT)LAYER_TYPE::MONSTER][i])->GetID();
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::MONSTER][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::MONSTER][i]->GetScale();
		int HP = dynamic_cast<CEditor_RenderDummy*>(m_arrObj[(UINT)LAYER_TYPE::MONSTER][i])->GetHP();
		float fDetectRange = dynamic_cast<CEditor_RenderDummy*>(m_arrObj[(UINT)LAYER_TYPE::MONSTER][i])->GetRange();

		fwrite(&ID, sizeof(OBJ_ID), 1, pFile);
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
		fwrite(&HP, sizeof(int), 1, pFile);
		fwrite(&fDetectRange, sizeof(float), 1, pFile);
	}

	fclose(pFile);
}

void CLevel::SaveTrap(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();
	if (SAVE_TYPE::STAGE01 == m_Save)
	{
		strFullPath += L"stage01\\";
	}

	else if (SAVE_TYPE::STAGE02 == m_Save)
	{
		strFullPath += L"stage02\\";
	}
	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"파일 개방 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::TRAP].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::TRAP].size(); ++i)
	{
		if (L"ERUPTION" == m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetName())
		{
			OBJ_ID ID = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetID();
			Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetPos();
			Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetScale();
			int HP = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetHp();
			float Range = dynamic_cast<CTrap_Eruption*>(m_arrObj[(UINT)LAYER_TYPE::TRAP][i])->GetRange();
			fwrite(&ID, sizeof(OBJ_ID), 1, pFile);
			fwrite(&vPos, sizeof(Vec2), 1, pFile);
			fwrite(&vScale, sizeof(Vec2), 1, pFile);
			fwrite(&HP, sizeof(int), 1, pFile);
			fwrite(&Range, sizeof(float), 1, pFile);
		}

		else
		{
			OBJ_ID ID = dynamic_cast<CEditor_RenderDummy*>(m_arrObj[(UINT)LAYER_TYPE::TRAP][i])->GetID();
			Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetPos();
			Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetScale();
			int HP = dynamic_cast<CEditor_RenderDummy*>(m_arrObj[(UINT)LAYER_TYPE::TRAP][i])->GetHP();
			float Range = dynamic_cast<CEditor_RenderDummy*>(m_arrObj[(UINT)LAYER_TYPE::TRAP][i])->GetRange();
			fwrite(&ID, sizeof(OBJ_ID), 1, pFile);
			fwrite(&vPos, sizeof(Vec2), 1, pFile);
			fwrite(&vScale, sizeof(Vec2), 1, pFile);
			fwrite(&HP, sizeof(int), 1, pFile);
			fwrite(&Range, sizeof(float), 1, pFile);
		}
	}

	fclose(pFile);
}

void CLevel::LoadPlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();
	if (L"Stage01" == GetName())
	{
		strFullPath += L"stage01\\";
	}

	else if (L"Stage02" == GetName())
	{
		strFullPath += L"stage02\\";
	}
	strFullPath += _strRelativePath;
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);


	if (nullptr == pFile)
		return;

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		CPlatform* pPlatform = new CPlatform(vPos, vScale);
		AddObject(LAYER_TYPE::PLATFORM, pPlatform);
	}

	fclose(pFile);
}

void CLevel::LoadLine(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();
	if (L"Stage01" == GetName())
	{
		strFullPath += L"stage01\\";
	}

	else if (L"Stage02" == GetName())
	{
		strFullPath += L"stage02\\";
	}
	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;
	
	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vStartPos;
		Vec2 vEndPos;

		fread(&vStartPos, sizeof(Vec2), 1, pFile);
		fread(&vEndPos, sizeof(Vec2), 1, pFile);

		CLine* pLine = new CLine(vStartPos, vEndPos);
		AddObject(LAYER_TYPE::LINE, pLine);
	}

	fclose(pFile);
}

void CLevel::LoadMonster(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	if (L"Stage01" == GetName())
	{
		strFullPath += L"stage01\\";
	}

	else if (L"Stage02" == GetName())
	{
		strFullPath += L"stage02\\";
	}
	
	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		OBJ_ID ID;
		Vec2 vPos;
		Vec2 vScale;
		int HP = 0;
		float DetectRange = 0.f;

		fread(&ID, sizeof(OBJ_ID), 1, pFile);
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);
		fread(&HP, sizeof(int), 1, pFile);
		fread(&DetectRange, sizeof(float), 1, pFile);

		if (OBJ_ID::METTOOL == ID)
		{
			// Mettool
			CMonster_Mettool* pMonster = new CMonster_Mettool(vPos, vScale, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::RAIDEN == ID)
		{
			// Raiden			
			CMonster_Raiden* pMonster = new CMonster_Raiden(vPos, vScale, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::GIGADEATH == ID)
		{
			// GIGADEATH
			CMonster_GigaDeath* pMonster = new CMonster_GigaDeath(vPos, vScale, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::BATTON == ID)
		{
			// BATTON
			CMonster_Batton* pMonster = new CMonster_Batton(vPos, vScale, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}
	}

	fclose(pFile);
}

void CLevel::LoadTrap(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();
	
	if (L"Stage01" == GetName())
	{
		strFullPath += L"stage01\\";
	}

	else if (L"Stage02" == GetName())
	{
		strFullPath += L"stage02\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		OBJ_ID ID;
		Vec2 vPos;
		Vec2 vScale;
		int HP = 0;
		float Range = 0.f;

		fread(&ID, sizeof(OBJ_ID), 1, pFile);
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);
		fread(&HP, sizeof(int), 1, pFile);
		fread(&Range, sizeof(float), 1, pFile);

		if (OBJ_ID::METEOR_DOWN == ID)
		{
			CTrap_Meteor* pTrap = new CTrap_Meteor(vPos, ID);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}

		else if (OBJ_ID::METEOR_UP == ID)
		{
			CTrap_Meteor* pTrap = new CTrap_Meteor(vPos, ID);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}

		else if (OBJ_ID::ERUPTION == ID)
		{
			CTrap_Eruption* pTrap = new CTrap_Eruption(vPos, ID);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}
	}

	fclose(pFile);
}

void CLevel::LoadDeathPlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	if (L"Stage01" == GetName())
	{
		strFullPath += L"stage01\\";
	}

	else if (L"Stage02" == GetName())
	{
		strFullPath += L"stage02\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"File 개방 실패", L"LINE", MB_OK);
		return;
	}

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;

		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		CPlatform_Death* pPlatform = new CPlatform_Death(vPos, vScale);
		AddObject(LAYER_TYPE::TILE, pPlatform);
	}

	fclose(pFile);
}

void CLevel::LoadEditorLine(const wstring& _strFilePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	strFullPath += _strFilePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"File 개방 실패", L"LINE", MB_OK);
		return;
	}

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vStartPos;
		Vec2 vEndPos;

		fread(&vStartPos, sizeof(Vec2), 1, pFile);
		fread(&vEndPos, sizeof(Vec2), 1, pFile);

		CLine* pLine = new CLine(vStartPos, vEndPos);
		AddObject(LAYER_TYPE::LINE, pLine);
	}

	fclose(pFile);
}

void CLevel::LoadEditorMonster(const wstring& _strFilePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	strFullPath += _strFilePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"File 개방 실패", L"MONSTER", MB_OK);
		return;
	}	

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		OBJ_ID ID;
		Vec2 vPos;
		Vec2 vScale;
		int HP = 0;
		float DetectRange = 0.f;

		fread(&ID, sizeof(OBJ_ID), 1, pFile);
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);
		fread(&HP, sizeof(int), 1, pFile);
		fread(&DetectRange, sizeof(float), 1, pFile);
		
		if (OBJ_ID::METTOOL == ID)
		{
			// Mettool
			CEditor_RenderDummy* pMonster = new CEditor_RenderDummy(vPos, vScale, ID, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::RAIDEN == ID)
		{
			// Raiden			
			CEditor_RenderDummy* pMonster = new CEditor_RenderDummy(vPos, vScale, ID, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::GIGADEATH == ID)
		{
			// GIGADEATH
			CEditor_RenderDummy* pMonster = new CEditor_RenderDummy(vPos, vScale, ID, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}

		else if (OBJ_ID::BATTON == ID)
		{
			// BATTON
			CEditor_RenderDummy* pMonster = new CEditor_RenderDummy(vPos, vScale, ID, HP, DetectRange);
			AddObject(LAYER_TYPE::MONSTER, pMonster);
		}
	}

	fclose(pFile);
}

void CLevel::LoadEditorTrap(const wstring& _strFilePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	strFullPath += _strFilePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"File 개방 실패", L"TRAP", MB_OK);
		return;
	}

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		OBJ_ID ID;
		Vec2 vPos;
		Vec2 vScale;
		int HP = 0;
		float Range = 0.f;

		fread(&ID, sizeof(OBJ_ID), 1, pFile);
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);
		fread(&HP, sizeof(int), 1, pFile);
		fread(&Range, sizeof(float), 1, pFile);

		if (OBJ_ID::METEOR_DOWN == ID)
		{
			CEditor_RenderDummy* pTrap = new CEditor_RenderDummy(vPos, vScale, ID, HP, Range);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}

		else if (OBJ_ID::METEOR_UP == ID)
		{
			CEditor_RenderDummy* pTrap = new CEditor_RenderDummy(vPos, vScale, ID, HP, Range);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}

		else if (OBJ_ID::ERUPTION == ID)
		{
			CTrap_Eruption* pTrap = new CTrap_Eruption(vPos, ID);
			AddObject(LAYER_TYPE::TRAP, pTrap);
		}
	}

	fclose(pFile);
}

void CLevel::LoadEditorDeathPlatform(const wstring& _strFilePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	strFullPath += _strFilePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"File 개방 실패", L"PLATFORM", MB_OK);
		return;
	}

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		CPlatform_Death* pPlatform = new CPlatform_Death(vPos, vScale);
		AddObject(LAYER_TYPE::TILE, pPlatform);

	}

	fclose(pFile);
}

void CLevel::LoadEditorPlatform(const wstring& _strFilePath)
{
	wstring strFullPath = CPathMgr::GetInst()->GetContehtPath();

	strFullPath += _strFilePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
	{
		MessageBox(CEngine::GetInst()->GetMainWnd(), L"File 개방 실패", L"PLATFORM", MB_OK);
		return;
	}

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;
		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		CPlatform* pPlatform = new CPlatform(vPos, vScale);
		AddObject(LAYER_TYPE::PLATFORM, pPlatform);
		
	}

	fclose(pFile);
}
