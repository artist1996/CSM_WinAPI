#include "pch.h"
#include "CBackGround.h"

CBackGround::CBackGround()
	: m_Img(nullptr)
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::tick()
{
}

void CBackGround::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vPos.x)
		, (int)(vPos.y)
		, GetImg()->GetWidth() * 2, GetImg()->GetHeight() * 2
		, GetImg()->GetDC(), 0, 0, GetImg()->GetWidth(), GetImg()->GetHeight(), bf);
}