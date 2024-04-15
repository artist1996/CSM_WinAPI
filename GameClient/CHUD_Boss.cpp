#include "pch.h"
#include "CHUD_Boss.h"

CHUD_Boss::CHUD_Boss()
	: m_Img(nullptr)
{
	SetPos(Vec2(700.f, 50.f));
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"BOSS_HUD", L"texture\\hud\\BossHP_UI.png");
}

CHUD_Boss::~CHUD_Boss()
{
}

void CHUD_Boss::tick_ui()
{
}

void CHUD_Boss::render_ui()
{
	Vec2 vPos = GetFinalPos();
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;


	AlphaBlend(DC, (int)vPos.x
		, (int)vPos.y
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC()
		, 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), bf);
}