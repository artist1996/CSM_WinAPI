#include "pch.h"
#include "CHUD_PlayerHP.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CHUD_PlayerHP::CHUD_PlayerHP()
	: m_Img(nullptr)
{
	SetPos(Vec2(57.f, 70.f));
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"GREENHP", L"texture\\hud\\HP_Bar.png");
	m_Owner = CLevelMgr::GetInst()->FindObjectByName(L"ZERO");
}

CHUD_PlayerHP::~CHUD_PlayerHP()
{
}

void CHUD_PlayerHP::tick_ui()
{
}

void CHUD_PlayerHP::render_ui()
{
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA; 

	Vec2 vPos = GetFinalPos();

	float hpRatio = static_cast<float>(m_Owner->GetHp()) / 15;
	int DrawHeight = static_cast<int>(m_Img->GetHeight() * hpRatio);

	AlphaBlend(DC, (int)vPos.x
		, (int)vPos.y + m_Img->GetHeight() - DrawHeight
		, m_Img->GetWidth(), DrawHeight
		, m_Img->GetDC()
		, 0, m_Img->GetHeight() - DrawHeight
		, m_Img->GetWidth(), DrawHeight, bf);
}