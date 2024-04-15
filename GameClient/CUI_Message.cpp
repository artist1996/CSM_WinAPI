#include "pch.h"
#include "CUI_Message.h"

CUI_Message::CUI_Message()
	: m_Img(nullptr)
	, m_Type(0)
{
}

CUI_Message::CUI_Message(Vec2 _Pos, int _Type)
	: m_Img(nullptr)
	, m_Type(_Type)
{
	SetPos(_Pos);
	m_CenterPos = _Pos;
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"MESSAGE", L"texture\\Select\\PlayerSelect.png");
}

CUI_Message::~CUI_Message()
{
}

void CUI_Message::tick_ui()
{
	Vec2 vPos = GetPos();

	if (0 == m_Type)
	{
		vPos += Vec2(1.f, 0.f) * 300.f * DT;
		SetPos(vPos);
	}

	else if (1 == m_Type)
	{
		vPos += Vec2(-1.f, 0.f) * 300.f * DT;
		SetPos(vPos);
	}

	if (abs(m_CenterPos.x - vPos.x) > 1600.f)
	{
		SetPos(m_CenterPos);
	}
}

void CUI_Message::render_ui()
{
	Vec2 vPos = GetPos();
	
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)vPos.x, (int)vPos.y
		, m_Img->GetWidth()
		, m_Img->GetHeight()
		, m_Img->GetDC()
		, 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), bf);
}
