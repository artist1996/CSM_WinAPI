#include "pch.h"
#include "CHUD_Player.h"

CHUD_Player::CHUD_Player()
	: m_HPBar(nullptr)
	, m_Life(nullptr)
{
	SetPos(Vec2(30.f, 50.f));
	m_HPBar = CAssetMgr::GetInst()->LoadTexture(L"PLAYER_HUD", L"texture\\hud\\HP_UI.png");
}

CHUD_Player::~CHUD_Player()
{
}

void CHUD_Player::tick_ui()
{
}

void CHUD_Player::render_ui()
{
	Vec2 vPos = GetFinalPos();
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;


	AlphaBlend(DC, (int)vPos.x
		, (int)vPos.y
		, m_HPBar->GetWidth(), m_HPBar->GetHeight()
		, m_HPBar->GetDC()
		, 0, 0
		, m_HPBar->GetWidth(), m_HPBar->GetHeight(), bf);
}

