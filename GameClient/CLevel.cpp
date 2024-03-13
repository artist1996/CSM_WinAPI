#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CCollider.h"
#include "CPathMgr.h"
#include "CPlatform.h"
#include "CLine.h"

CLevel::CLevel()
	: m_Platform(nullptr)
	, m_Line(nullptr)
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

void CLevel::LoadFromPlatform(const wstring& _strRelativePath)
{
	m_vecEditPlat.clear();
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

void CLevel::LoadFromLine(const wstring& _strRelativePath)
{
	m_vecEditLine.clear();
	wstring strPath = CPathMgr::GetInst()->GetContehtPath();
	strPath += _strRelativePath;

	FILE* pFile = nullptr;
	
	_wfopen_s(&pFile, strPath.c_str(), L"rb");

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vStartPos;
		Vec2 vEndPos;

		fread(&vStartPos, sizeof(Vec2), 1, pFile);
		fread(&vEndPos, sizeof(Vec2), 1, pFile);

		m_Line = new CLine(vStartPos, vEndPos);
		m_vecEditLine.push_back(m_Line);
		AddObject(LAYER_TYPE::LINE, m_vecEditLine[i]);
	}

	fclose(pFile);
}
