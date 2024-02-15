#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CAssetMgr::CAssetMgr()
{
}

CAssetMgr::~CAssetMgr()
{
	Safe_Del_Map(m_mapTex);

	Safe_Del_Map(m_mapSound);
}

void CAssetMgr::init()
{
	
}

CTexture* CAssetMgr::LoadTexture(const wstring& _Key, const wstring& _strRelativePath)
{
	// �̹� �ش� Ű�� ��ϵ� �ؽ��İ� ������
	CTexture* pTex = FindTexture(_Key);
	if (nullptr != pTex)
	{
		return pTex;
	}

	// Full Path �� �����
	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();
	strFilePath += _strRelativePath;

	// �ؽ��� ��ü ����
	// �ؽ��� �ε�
	pTex = new CTexture;
	if (FAILED(pTex->Load(strFilePath)))
	{
		MessageBox(nullptr, _strRelativePath.c_str(), L"�ؽ��� �ε� ����", MB_OK);
		delete pTex;

		return nullptr;
	}

	// map �� �ε��� �ؽ��ĸ� ���
	m_mapTex.insert(make_pair(_Key, pTex));

	// �ؽ��� ���¿� ������ Ű���� ����θ� �˷���
	pTex->m_Key = _Key;
	pTex->m_RelativePath = _strRelativePath;

	return pTex;
}

CTexture* CAssetMgr::FindTexture(const wstring& _Key)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_Key);

	if (iter == m_mapTex.end())
		return nullptr;

	return iter->second;
}
