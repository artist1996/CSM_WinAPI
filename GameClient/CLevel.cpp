#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CCollider.h"
#include "CPathMgr.h"
#include "CPlatform.h"
#include "CLine.h"
#include "CMonster.h"
#include "CMonster_Mettool.h"

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
		OBJ_ID ID = m_arrObj[(UINT)LAYER_TYPE::MONSTER][i]->GetID();
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::MONSTER][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::MONSTER][i]->GetScale();
		int HP = dynamic_cast<CMonster*>(m_arrObj[(UINT)LAYER_TYPE::MONSTER][i])->GetHP();
		float fDetectRange = dynamic_cast<CMonster*>(m_arrObj[(UINT)LAYER_TYPE::MONSTER][i])->GetDetectRange();

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
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::TRAP][i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
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
			

		}

		else if (OBJ_ID::GIGADEATH == ID)
		{
			// GIGADEATH
			

		}

		else if (OBJ_ID::BATTON == ID)
		{
			// BATTON


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
		Vec2 vPos;
		Vec2 vScale;

		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		CMonster* pMonster = new CMonster(vPos, vScale);
		AddObject(LAYER_TYPE::MONSTER, pMonster);
	}

	fclose(pFile);
}
