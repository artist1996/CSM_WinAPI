#include "pch.h"
#include "CAnimation.h"

#include "CObj.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTexture.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CLevelMgr.h"

#include "CLevel.h"

CAnimation::CAnimation()
	: m_Animator(nullptr)
	, m_Atlas(nullptr)
	, m_Time(0.f)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
	, m_OldBrush(nullptr)
	, m_Hit(false)
{
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"HIT_LEFT", L"texture\\MagmaDragoon_HITLEFT.png");
	pTex = CAssetMgr::GetInst()->LoadTexture(L"HIT_RIGHT", L"texture\\MagmaDragoon_HITRIGHT.png");
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

	// 오브젝트의 렌더링 위치
	Vec2 vRenderPos = pOwnerObj->GetRenderPos();

	// 현재 프레임 이미지를 오브젝트 위치에 렌더링
	
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	if (L"TOOL" == pLevel->GetName())
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;
		CObj* DummyObject = m_Animator->GetOwner();
		Vec2 vPos = DummyObject->GetPos();

		AlphaBlend(DC, (int)(vPos.x - frm.SliceSize.x * 0.5f) + (int)frm.Offset.x
			, (int)(vPos.y - frm.SliceSize.y) + (int)frm.Offset.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y
			, m_Atlas->GetDC()
			, (int)frm.StartPos.x, (int)frm.StartPos.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
	}
	
	if (L"Shadow" == pOwnerObj->GetName())
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 70;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x * 0.5f) + (int)frm.Offset.x
			, (int)(vRenderPos.y - frm.SliceSize.y) + (int)frm.Offset.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y
			, m_Atlas->GetDC()
			, (int)frm.StartPos.x, (int)frm.StartPos.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
	}

	if (LAYER_TYPE::DUMMY == pOwnerObj->GetLayerType())
	{
		BLENDFUNCTION bf = {};
	
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;
	
		AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x * 0.5f) + (int)frm.Offset.x
			, (int)(vRenderPos.y - frm.SliceSize.y) + (int)frm.Offset.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y
			, m_Atlas->GetDC()
			, (int)frm.StartPos.x, (int)frm.StartPos.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
	}

	if (LAYER_TYPE::BOSS == pOwnerObj->GetLayerType())
	{
		if (pOwnerObj->IsHit())
		{
			if (DIRECTION::LEFT == pOwnerObj->GetDirection())
			{
				m_Atlas = CAssetMgr::GetInst()->FindTexture(L"HIT_LEFT");
			}

			else if (DIRECTION::RIGHT == pOwnerObj->GetDirection())
			{
				m_Atlas = CAssetMgr::GetInst()->FindTexture(L"HIT_RIGHT");
			}

			BLENDFUNCTION bf = {};

			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = 205;
			bf.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x * 0.5f) + (int)frm.Offset.x
				, (int)(vRenderPos.y - frm.SliceSize.y) + (int)frm.Offset.y
				, (int)frm.SliceSize.x, (int)frm.SliceSize.y
				, m_Atlas->GetDC()
				, (int)frm.StartPos.x, (int)frm.StartPos.y
				, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
		}

		else
		{
			if (DIRECTION::LEFT == pOwnerObj->GetDirection())
			{
				m_Atlas = CAssetMgr::GetInst()->FindTexture(L"DRAGOON_LEFT");
			}

			else if (DIRECTION::RIGHT == pOwnerObj->GetDirection())
			{
				m_Atlas = CAssetMgr::GetInst()->FindTexture(L"DRAGOON_RIGHT");
			}
			
			BLENDFUNCTION bf = {};

			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = 255;
			bf.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x * 0.5f) + (int)frm.Offset.x
				, (int)(vRenderPos.y - frm.SliceSize.y) + (int)frm.Offset.y
				, (int)frm.SliceSize.x, (int)frm.SliceSize.y
				, m_Atlas->GetDC()
				, (int)frm.StartPos.x, (int)frm.StartPos.y
				, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
		}
	}

	if (LAYER_TYPE::MONSTER == pOwnerObj->GetLayerType()
		|| LAYER_TYPE::TRAP == pOwnerObj->GetLayerType() 
		|| LAYER_TYPE::MONSTER_MISSILE == pOwnerObj->GetLayerType()
		|| LAYER_TYPE::BOSS_ATTACK == pOwnerObj->GetLayerType())
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x * 0.5f) + (int)frm.Offset.x
			, (int)(vRenderPos.y - frm.SliceSize.y) + (int)frm.Offset.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y
			, m_Atlas->GetDC()
			, (int)frm.StartPos.x, (int)frm.StartPos.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
		
	}

	if (L"ZERO" == pOwnerObj->GetName())
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC, (int)(vRenderPos.x - frm.SliceSize.x * 0.5f) + (int)frm.Offset.x
			, (int)(vRenderPos.y - frm.SliceSize.y) + (int)frm.Offset.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y
			, m_Atlas->GetDC()
			, (int)frm.StartPos.x, (int)frm.StartPos.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
		return;
	}

	if (L"Logo" == m_Animator->GetOwner()->GetName())
	{
		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;
		CObj* DummyObject = m_Animator->GetOwner();
		Vec2 vPos = DummyObject->GetPos();

		AlphaBlend(DC, (int)(vPos.x) + (int)frm.Offset.x,
			(int)(vPos.y) + (int)frm.Offset.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y
			, m_Atlas->GetDC()
			, (int)frm.StartPos.x, (int)frm.StartPos.y
			, (int)frm.SliceSize.x, (int)frm.SliceSize.y, bf);
		return;
	}	
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

void CAnimation::Create(CTexture* _AtlasTex, vector<tAnimFrm> _vecFrm)
{
	m_Atlas = _AtlasTex;

	for (int i = 0; i < _vecFrm.size(); ++i)	
	{
		tAnimFrm frm = {};
		frm.Duration = _vecFrm[i].Duration;
		frm.StartPos = _vecFrm[i].StartPos;
		frm.SliceSize = _vecFrm[i].SliceSize;
		frm.Offset = _vecFrm[i].Offset;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativeFolderPath)
{
	// Save 함수 개선
	//wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();	// 컨텐츠 패스(절대경로)
	//strFilePath += _strRelativeFolderPath;						// 상대 경로
	//strFilePath += GetName();										// 파일 이름
	//strFilePath += L".anim";										// 확장자 명

	wstring strFilePath = _strRelativeFolderPath;
	strFilePath += L".anim";

	FILE* pFile = nullptr;				// 파일
	_wfopen_s(&pFile, strFilePath.c_str(), L"w");		// 문자열을 저장할 것이기 때문에 wb가 아닌 w로 파일 개방

	if (nullptr == pFile)								// pFile이 nullptr이면 파일 개방 실패 했기 때문에 return 해버림
		return;

	// 애니메이션의 이름을 먼저 저장
	fwprintf_s(pFile, L"[ANIMATION_NAME]\n");
	
	wstring strAnimName = GetName();
	fwprintf_s(pFile, L"%s\n\n", strAnimName.c_str());

	// 아틀라스 이미지 정보 저장

	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");

	if (nullptr == m_Atlas)
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", L"None");
		fwprintf_s(pFile, L"[ATLAS_PATH]\t%s\n", L"None");
	}

	else
	{
		fwprintf_s(pFile, L"[ATLAS_KEY]\t%s\n", m_Atlas->GetKey().c_str());
		fwprintf_s(pFile, L"[ATLAS_PATH]\t%s\n", m_Atlas->GetRelativePath().c_str());
	}

	fwprintf_s(pFile, L"\n");

	// 프레임 정보 저장
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", (int)m_vecFrm.size());	

	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[FRAME_INDEX]\t%d\n", (int)i);
		fwprintf_s(pFile, L"[START_POS]\t%f  %f\n", m_vecFrm[i].StartPos.x, m_vecFrm[i].StartPos.y);
		fwprintf_s(pFile, L"[SLICE_SIZE]\t\t%f  %f\n", m_vecFrm[i].SliceSize.x, m_vecFrm[i].SliceSize.y);
		fwprintf_s(pFile, L"[OFFSET]\t\t%f  %f\n", m_vecFrm[i].Offset.x, m_vecFrm[i].Offset.y);
		fwprintf_s(pFile, L"[DURATION]  \t%f\n", m_vecFrm[i].Duration);
		fwprintf_s(pFile, L"\n");
	}

	fclose(pFile);
}

int CAnimation::Load(const wstring& _strRelativeFilePath)
{
	// Load 함수 개선

	wstring strFilePath = CPathMgr::GetInst()->GetContehtPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;

	// 파일 개방
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	// nullptr 이면 개방 실패 return
	if (nullptr == pFile)
	{
		return E_FAIL;
	}


	// 애니메이션 이름 읽어오기
	wchar_t szBuff[256] = {};

	// 정보 읽어오기
	// 파일의 끝에 도달하면 읽어드릴 데이터가 없기 때문에 EOF(-1)을 반환한다.
	while (EOF != fwscanf_s(pFile, L"%s", szBuff, 256))
	{
		wstring strRead = szBuff;

		if (L"[ANIMATION_NAME]" == strRead)
		{
			// 한번 더 읽어오고 SetName함수 호출 해서 이름 세팅해준다.
			fwscanf_s(pFile,L"%s", szBuff, 256);
			SetName(szBuff);
		}

		else if (L"[ATLAS_TEXTURE]" == strRead)
		{
			// 아틀라스의 정보를 저장시킨다.
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

		else if (L"[FRAME_COUNT]" == strRead)
		{
			// FrameCount 받아와서 반복문 돌려준다.
			int FrmCount = 0;
			fwscanf_s(pFile, L"%d", &FrmCount);

			for (int i = 0; i < FrmCount; ++i)
			{
				tAnimFrm frm = {};
				// START POS 가 나올 때 까지 읽는다.
				do { fwscanf_s(pFile, L"%s", szBuff, 256); }
				while (wcscmp(szBuff, L"[START_POS]"));

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

int CAnimation::LoadAnimation(const wstring& _strFullPath)
{
	wstring strFilePath = _strFullPath;

	FILE* pFile = nullptr;

	// 파일 개방
	_wfopen_s(&pFile, strFilePath.c_str(), L"r");

	// nullptr 이면 개방 실패 return
	if (nullptr == pFile)
	{
		return E_FAIL;
	}


	// 애니메이션 이름 읽어오기
	wchar_t szBuff[256] = {};

	// 정보 읽어오기
	// 파일의 끝에 도달하면 읽어드릴 데이터가 없기 때문에 EOF(-1)을 반환한다.
	while (EOF != fwscanf_s(pFile, L"%s", szBuff, 256))
	{
		wstring strRead = szBuff;

		if (L"[ANIMATION_NAME]" == strRead)
		{
			// 한번 더 읽어오고 SetName함수 호출 해서 이름 세팅해준다.
			fwscanf_s(pFile, L"%s", szBuff, 256);
			SetName(szBuff);
		}

		else if (L"[ATLAS_TEXTURE]" == strRead)
		{
			// 아틀라스의 정보를 저장시킨다.
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

		else if (L"[FRAME_COUNT]" == strRead)
		{
			// FrameCount 받아와서 반복문 돌려준다.
			int FrmCount = 0;
			fwscanf_s(pFile, L"%d", &FrmCount);

			for (int i = 0; i < FrmCount; ++i)
			{
				tAnimFrm frm = {};
				// START POS 가 나올 때 까지 읽는다.
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
