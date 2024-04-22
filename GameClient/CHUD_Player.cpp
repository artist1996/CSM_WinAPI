#include "pch.h"
#include "CHUD_Player.h"

#include "CLevelMgr.h"

CHUD_Player::CHUD_Player()
	: m_HPBar(nullptr)
	, m_Owner(nullptr)
{
	SetName(L"PLAYERHUD");
	m_Owner = CLevelMgr::GetInst()->FindObjectByName(L"ZERO");

	SetPos(Vec2(30.f, 50.f));
	m_HPBar = CAssetMgr::GetInst()->LoadTexture(L"PLAYER_HUD2", L"texture\\hud\\HP_UI2.png");
	m_HPBar = CAssetMgr::GetInst()->LoadTexture(L"PLAYER_HUD", L"texture\\hud\\HP_UI.png");
}

CHUD_Player::~CHUD_Player()
{
}

void CHUD_Player::tick_ui()
{
	if (2 == m_Owner->GetLife())
	{
		m_HPBar = CAssetMgr::GetInst()->FindTexture(L"PLAYER_HUD");
	}

	else if (1 == m_Owner->GetLife())
	{
		m_HPBar = CAssetMgr::GetInst()->FindTexture(L"PLAYER_HUD2");
	}

	else
		return;
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

