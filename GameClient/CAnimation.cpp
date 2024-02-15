#include "pch.h"
#include "CAnimation.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"


CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_Atlas(nullptr)
	, m_Time(0.f)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
{

}

CAnimation::~CAnimation()
{

}

void CAnimation::finaltick()
{
	if (m_bFinish)
		return;

	// ���� ������ ����
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	m_Time += DT;

	if (frm.Duration <= m_Time)
	{		
		m_Time -= frm.Duration;
		++m_CurFrmIdx;

		// �������� �������� �����ߴ�.
		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			--m_CurFrmIdx;
			m_bFinish = true;
		}
	}
}

void CAnimation::render()
{
	// ���� ������ ����
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	// Animation �� ����ϰ��ִ� ������Ʈ
	CObj* pOwnerObj = m_Animator->GetOwner();

	// ������Ʈ�� ��ġ
	Vec2 vPos = pOwnerObj->GetPos();

	// ���� ������ �̹����� ������Ʈ ��ġ�� ������
	TransparentBlt(	  DC
					, vPos.x - frm.SliceSize.x / 2.f
					, vPos.y - frm.SliceSize.y / 2.f
					, frm.SliceSize.x, frm.SliceSize.y
					, m_Atlas->GetDC()
					, frm.StartPos.x, frm.StartPos.y
					, frm.SliceSize.x, frm.SliceSize.y
					, RGB(255, 0, 255));
}

void CAnimation::Create(  CTexture* _AtlasTex, Vec2 _StartPos
						, Vec2 _SliceSize, int _FrameCount, int _FPS)
{
	m_Atlas = _AtlasTex;

	// ������ ���� ����
	for (int i = 0; i < _FrameCount; ++i)
	{
		tAnimFrm frm = {};
		frm.Duration = 1.f / (float)_FPS;
		frm.StartPos = _StartPos + Vec2(_SliceSize.x * i, 0.f);
		frm.SliceSize = _SliceSize;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativeFolderPath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();	// ���� ��� ����
	strFilePath += _strRelativeFolderPath;							// ��� ��� ����
	strFilePath += GetName();										// ���� �̸�
	strFilePath += L".anim";										// Ȯ���� ��

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");					// ���� ���� ���ѳ�

	if (nullptr == pFile)	// ���� �ߴµ� nullptr�̸�
	{
		return;	// ���� �ϱ� return ��������
	}

	// ������ ���� ����
	size_t FrmCount = m_vecFrm.size();			// ������ ������ ���� ���� �� �ű� ������ Frame vector�� ����� ����.

	for (size_t i = 0; i < FrmCount; ++i)
	{
		// ������ ������? �ش� �������� ����
		tAnimFrm frm = {};
		frm.StartPos = m_vecFrm[i].StartPos;
		frm.SliceSize = m_vecFrm[i].SliceSize;
		frm.Duration = m_vecFrm[i].Duration;
		// pFile�� ������
		fwrite(&frm, sizeof(tAnimFrm),1, pFile);
	}

	// ��Ʋ�� ���� ����
	bool bAtlasTex = false;
	if (nullptr != m_Atlas)
	{
		bAtlasTex = true;
	}

	fwrite(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex)
	{
		wstring strKey = m_Atlas->GetKey();
		size_t len = strKey.length();
		fwrite(&len, sizeof(size_t), 1, pFile);
		fwrite(strKey.c_str(), sizeof(wchar_t), len, pFile);

		wstring strRelativePath = m_Atlas->GetRelativePath();
		len = strRelativePath.length();
		fwrite(&len, sizeof(size_t), 1, pFile);
		fwrite(strRelativePath.c_str(), sizeof(wchar_t), len, pFile);
	}

	// ���� �ݱ�
	fclose(pFile);
}

int CAnimation::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();
	strFilePath += _strRelativeFilePath;
	
	FILE* pFile = nullptr;
	
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	
	if (nullptr == pFile)
		return E_FAIL;

	// ������ ���� �о����
	size_t FrmCount = 0;
	fread(&FrmCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < FrmCount; ++i)
	{
		tAnimFrm frm = {};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}


	// ��Ʋ�� ���� �о����
	bool bAtlasTex = false;
	fread(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex) // true��� ���� �������.
	{
		size_t len = 0;
		fread(&len, sizeof(size_t), 1, pFile);
		wchar_t szBuff[256] = {};

		fread(&szBuff, sizeof(wchar_t), len, pFile);

		wstring strKey = szBuff;

		wstring strFilePath;
	}
	
	return S_OK;
}