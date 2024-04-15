#include "pch.h"
#include "CHUD_BossHP.h"
#include "CLevelMgr.h"
#include "CLevel.h"

CHUD_BossHP::CHUD_BossHP()
	: m_Img(nullptr)
{
	SetPos(Vec2(739.f, 58.f));
	m_Owner = CLevelMgr::GetInst()->FindObjectByName(L"Dragoon");
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"BossHP_Bar", L"texture\\hud\\BossHP_Bar.png");
}

CHUD_BossHP::~CHUD_BossHP()
{
}

void CHUD_BossHP::tick_ui()
{
}

void CHUD_BossHP::render_ui()
{
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	Vec2 vPos = GetFinalPos();

	float hpRatio = static_cast<float>(m_Owner->GetHp()) / 30;
	int DrawHeight = static_cast<int>(m_Img->GetHeight() * hpRatio);

	AlphaBlend(DC, (int)vPos.x
		, (int)vPos.y + m_Img->GetHeight() - DrawHeight
		, m_Img->GetWidth(), DrawHeight
		, m_Img->GetDC()
		, 0, m_Img->GetHeight() - DrawHeight
		, m_Img->GetWidth(), DrawHeight, bf);
}