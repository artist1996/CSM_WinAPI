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
	// Save �Լ� ����
	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();	// ������ �н�(������)
	strFilePath += _strRelativeFolderPath;							// ��� ���
	strFilePath += GetName();										// ���� �̸�
	strFilePath += L".anim";										// Ȯ���� ��

	FILE* pFile = nullptr;				// ����
	_wfopen_s(&pFile, strFilePath.c_str(), L"w");		// ���ڿ��� ������ ���̱� ������ wb�� �ƴ� w�� ���� ����

	if (nullptr == pFile)								// pFile�� nullptr�̸� ���� ���� ���� �߱� ������ return �ع���
		return;

	// �ִϸ��̼��� �̸��� ���� ����
	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	
	wstring strAnimName = GetName();
	fwprintf_s(pFile, L"%s\n\n", strAnimName.c_str());

	// ��Ʋ�� �̹��� ���� ����

	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");

	if (nullptr == m_Atlas)
	{
		fwprintf_s(pFile, L"[KEY]\t%s\n", L"None");
		fwprintf_s(pFile, L"[PATH]\t%s\n", L"None");
	}

	else
	{
		fwprintf_s(pFile, L"[KEY]\t%s\n", m_Atlas->GetKey().c_str());
		fwprintf_s(pFile, L"[PATH]\t%s\n", m_Atlas->GetRelativePath().c_str());
	}

	fwprintf_s(pFile, L"\n");

	// ������ ���� ����
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", (int)m_vecFrm.size());	

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[FRAME_INDEX]\n%d\n", (int)i);
		fwprintf_s(pFile, L"[STATR_POS]\t%f %f\n", m_vecFrm[i].StartPos.x, m_vecFrm[i].StartPos.y);
		fwprintf_s(pFile, L"[SLICE_SIZE]\t\t%f %f\n", m_vecFrm[i].SliceSize.x, m_vecFrm[i].SliceSize.y);
		fwprintf_s(pFile, L"[OFFSET]\t\t%f %f\n", m_vecFrm[i].Offset.x, m_vecFrm[i].Offset.y);
		fwprintf_s(pFile, L"[DURATION]\t%f\n", m_vecFrm[i].Duration);

		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

int CAnimation::Load(const wstring& _strRelativeFilePath)
{
	// Load �Լ� ����

	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;

	// ���� ����
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	// nullptr �̸� ���� ���� return
	if (nullptr == pFile)
	{
		return E_FAIL;
	}


	// �ִϸ��̼� �̸� �о����
	wchar_t szBuff[256] = {};

	// ���� �о����
	// ������ ���� �����ϸ� �о�帱 �����Ͱ� ���� ������ EOF(-1)�� ��ȯ�Ѵ�.
	while (EOF != fwscanf_s(pFile, szBuff, 256))
	{
		if (L"[ANIMATION_NAME]" == szBuff)
		{
			// �ѹ� �� �о���� SetName�Լ� ȣ�� �ؼ� �̸� �������ش�.
			fwscanf_s(pFile,L"%s", szBuff, 256);
			SetName(szBuff);
		}

		else if (L"[ATLAS_TEXTURE]" == szBuff)
		{
			// ��Ʋ���� ������ �����Ų��.
			fwscanf_s(pFile, L"%s", szBuff, 256);
			fwscanf_s(pFile, L"%s", szBuff, 256);
			wstring strKey = szBuff;

			fwscanf_s(pFile, L"%s", szBuff, 256);
			fwscanf_s(pFile, L"%s", szBuff, 256);
			wstring strPath = szBuff;

			if (L"None" != strKey && L"None" != strPath)
			{
				m_Atlas = CAssetMgr::GetInst()->LoadTexture(strKey, strPath);
			}
		}

		else if (L"[FRAME_COUNT]" == szBuff)
		{
			// FrameCount �޾ƿͼ� �ݺ��� �����ش�.
			int FrmCount = 0;
			fwscanf_s(pFile, L"%d", FrmCount);

			for (int i = 0; i < FrmCount; ++i)
			{
				tAnimFrm frm = {};
				// START POS �� ���� �� ���� �д´�.
				do { fwscanf_s(pFile, L"%s", szBuff, 256); } while (wcscmp(szBuff, L"[START_POS]"));

				fwscanf_s(pFile, L"%f%f", &frm.StartPos.x, &frm.StartPos.y);
				fwscanf_s(pFile, L"%s", szBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.SliceSize.x, &frm.SliceSize.y);
				fwscanf_s(pFile, L"%s", szBuff, 256);
				fwscanf_s(pFile, L"%f%f", &frm.Offset.x, &frm.Offset.y);
				fwscanf_s(pFile, L"%s", szBuff, 256);
				fwscanf_s(pFile, L"%f", &frm.Duration);

				m_vecFrm.push_back(frm);
			}
		}
	}

	


	return S_OK;
}