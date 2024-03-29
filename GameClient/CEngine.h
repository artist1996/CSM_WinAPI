#pragma once

class CTexture;

// 게임 최고 관리자
class CEngine
{
	SINGLE(CEngine)
private:
	HINSTANCE	m_hInstance;	// 프로세스 메모리 핸들
	HWND		m_hMainWnd;		// 메인 윈도우 핸들
	POINT		m_Resolution;	// 메인 윈도우 해상도
	HDC			m_hDC;			// 메인 윈도우 DC

	CTexture*	m_SubTex;

	HPEN		m_arrPen[(UINT)PEN_TYPE::END];
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];

public:
	int init(HINSTANCE _hInst, HWND _hWnd, POINT _Resolution);
	void progress();

private:
	void CreateDefaultGDIObject();


public:
	HINSTANCE GetProcessInstance() { return m_hInstance; }
	HWND GetMainWnd() { return m_hMainWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetSubDC();

	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[(UINT)_type]; }
	HBRUSH GetBrush(BRUSH_TYPE _type) { return m_arrBrush[(UINT)_type]; }

	Vec2 GetResolution() { return m_Resolution; }

	void ChangeWindowSize(Vec2 _Resoultion, bool _bMenu);
};


