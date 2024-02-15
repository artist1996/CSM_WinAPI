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

	// 현재 프레임 정보
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	m_Time += DT;

	if (frm.Duration <= m_Time)
	{		
		m_Time -= frm.Duration;
		++m_CurFrmIdx;

		// 프레임이 마지막에 도달했다.
		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			--m_CurFrmIdx;
			m_bFinish = true;
		}
	}
}

void CAnimation::render()
{
	// 현재 프레임 정보
	const tAnimFrm& frm = m_vecFrm[m_CurFrmIdx];

	// Animation 을 재생하고있는 오브젝트
	CObj* pOwnerObj = m_Animator->GetOwner();

	// 오브젝트의 위치
	Vec2 vPos = pOwnerObj->GetPos();

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
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

	// 프레임 정보 생성
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
	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();	// 절대 경로 얻어옴
	strFilePath += _strRelativeFolderPath;							// 상대 경로 지정
	strFilePath += GetName();										// 파일 이름
	strFilePath += L".anim";										// 확장자 명

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");					// 파일 개방 시켜놈

	if (nullptr == pFile)	// 개방 했는데 nullptr이면
	{
		return;	// 에러 니까 return 때려버림
	}

	// 프레임 정보 저장
	size_t FrmCount = m_vecFrm.size();			// 프레임 정보를 각각 저장 할 거기 떄문에 Frame vector의 사이즈를 들고옴.

	for (size_t i = 0; i < FrmCount; ++i)
	{
		// 저장할 정보는? 해당 프레임의 정보
		tAnimFrm frm = {};
		frm.StartPos = m_vecFrm[i].StartPos;
		frm.SliceSize = m_vecFrm[i].SliceSize;
		frm.Duration = m_vecFrm[i].Duration;
		// pFile이 마지막
		fwrite(&frm, sizeof(tAnimFrm),1, pFile);
	}

	// 아틀라스 정보 저장
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

	// 파일 닫기
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

	// 프레임 정보 읽어오기
	size_t FrmCount = 0;
	fread(&FrmCount, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < FrmCount; ++i)
	{
		tAnimFrm frm = {};
		fread(&frm, sizeof(tAnimFrm), 1, pFile);
		m_vecFrm.push_back(frm);
	}


	// 아틀라스 정보 읽어오기
	bool bAtlasTex = false;
	fread(&bAtlasTex, sizeof(bool), 1, pFile);

	if (bAtlasTex) // true라면 정보 들어있음.
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