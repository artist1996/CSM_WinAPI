#include "pch.h"
#include "CEngine.h"

#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CDbgRender.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CAssetMgr.h"
#include "CTaskMgr.h"
#include "CCamera.h"
#include "CSoundMgr.h"
#include "CTexture.h"
#include "CPlayerEffectMgr.h"



CEngine::CEngine()
	: m_hMainWnd(nullptr)	
	, m_Resolution{}
	, m_hDC(nullptr)
	, m_SubTex(nullptr)
	, m_arrPen{}
	, m_arrBrush{}
{
}

CEngine::~CEngine()
{
	// DC 삭제
	ReleaseDC(m_hMainWnd, m_hDC);

	// Pen 삭제
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	// Brush 삭제
	for (int i = 0; i < 4; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}
}

int CEngine::init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution)
{
	m_hInstance = _hInst;
	m_hMainWnd = _hWnd;
	m_Resolution = _Resolution;

	// 윈도우 크기를 변경
	ChangeWindowSize(m_Resolution, false);

	// DC 및 펜, 브러쉬 생성
	CreateDefaultGDIObject();	

	// Manager 초기화
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();

	CAssetMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();


	CCamera::GetInst()->init();
	CSoundMgr::GetInst()->init();


	return S_OK;
}

void CEngine::progress()
{	
	// ============
	// Manager Tick
	// ============
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	CDbgRender::GetInst()->tick();
	CCamera::GetInst()->tick();

	// ==============
	// Level Progress
	// ==============
	CLevelMgr::GetInst()->progress();
	CPlayerEffectMgr::GetInst()->tick();
	CCollisionMgr::GetInst()->tick();

	// =========
	// Rendering
	// =========
	// 화면 Clear
	{
		USE_BRUSH(m_SubTex->GetDC(), BRUSH_TYPE::BRUSH_GRAY);
		Rectangle(m_SubTex->GetDC(), -1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	}

	CLevelMgr::GetInst()->render();	
	CCamera::GetInst()->render();
	CDbgRender::GetInst()->render();


	// Sub -> Main
	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_SubTex->GetDC(), 0, 0, SRCCOPY);

	// =========
	// Task 처리
	// =========
	CTaskMgr::GetInst()->tick();
}

void CEngine::CreateDefaultGDIObject()
{	
	// 메인 윈도우를 타겟으로 지정하는 DC 생성
	m_hDC = ::GetDC(m_hMainWnd);
	
	m_SubTex = CAssetMgr::GetInst()->CreateTexture(L"SubTexture", (UINT)m_Resolution.x, (UINT)m_Resolution.y);

	//m_SubTex = CAssetMgr::GetInst()->CreateTexture(L"SubTexture", (UINT)640, (UINT)480);

	// 자주 사용할 펜 생성
	m_arrPen[(UINT)PEN_TYPE::PEN_RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::PEN_BLACK] = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	
	// 자주 사용할 브러쉬 생성
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_GRAY] = CreateSolidBrush(RGB(100, 100, 100));
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BRUSH_BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
}

HDC CEngine::GetSubDC()
{
	return m_SubTex->GetDC();
}

void CEngine::ChangeWindowSize(Vec2 _Resolution, bool _bMenu)
{
	// 입력된 해상도를 가져가기 위한 실제 윈도우의 크기를 계산
	m_Resolution.x = (int)_Resolution.x;
	m_Resolution.y = (int)_Resolution.y;

	RECT rt = { 0, 0, _Resolution.x, _Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);

	// 윈도우 크기를 변경
	SetWindowPos(m_hMainWnd, nullptr, 300, 50, rt.right - rt.left, rt.bottom - rt.top, 0);
}