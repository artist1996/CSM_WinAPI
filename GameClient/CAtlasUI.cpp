#include "pch.h"
#include "resource.h"
#include "CAtlasUI.h"
#include "CTexture.h"

CAtlasUI::CAtlasUI()
	: m_Texture(nullptr)
	, m_bMouse(false)
{
	SetName(L"AtlasUI");
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"ZERO_RIGHT", L"texture\\ZERO_RIGHT.png");
	m_vecTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->LoadTexture(L"GIGA_ATTACK", L"texture\\RAKUHOUHA.png");
	m_vecTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->LoadTexture(L"ZERO", L"texture\\ZERO.png");
	m_vecTex.push_back(pTex);
	pTex = CAssetMgr::GetInst()->LoadTexture(L"Title", L"texture\\Title.png");
	m_vecTex.push_back(pTex);
}

CAtlasUI::~CAtlasUI()
{
	//Safe_Del_Vec(m_vecTex);
}

void CAtlasUI::tick_ui()
{
	if (IsMouseOn())
	{
		if (m_bMouse)
		{
			if (KEY_TAP(KEY::LBTN))
			{
				ResetCutInfo();
				m_CutInfo.Start = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			}
	
			else if (KEY_PRESSED(KEY::LBTN))
			{
				m_CutInfo.End = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			}
	
			else if (KEY_RELEASED(KEY::LBTN))
			{
				m_bMouse = false;
				m_CutInfo.End = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
			}
		}
	}
}

void CAtlasUI::render_ui()
{
	CUI::render_ui();

	USE_PEN(DC, PEN_TYPE::PEN_BLACK);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);
	CUT_INFO CutInfo = m_CutInfo;
	Vec2 Start = CCamera::GetInst()->GetRenderPos(CutInfo.Start);
	Vec2 End = CCamera::GetInst()->GetRenderPos(CutInfo.End);
	Rectangle(DC, (int)Start.x, (int)Start.y, (int)End.x, (int)End.y);
	
	if (nullptr == m_Texture)
		return;
	
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	AlphaBlend(DC, (int)vPos.x, (int)vPos.y, (int)(m_Texture->GetWidth()), (int)(m_Texture->GetHeight())
			 , m_Texture->GetDC(), 0, 0, m_Texture->GetWidth(), m_Texture->GetHeight(), bf);
}

void CAtlasUI::SetAtlasTexture(const wstring& _strName)
{
	m_Texture = CAssetMgr::GetInst()->FindTexture(_strName);
}
