#include "pch.h"
#include "CDummy_Magma.h"

CDummy_Magma::CDummy_Magma()
	: m_Img(nullptr)
{
	SetPos(Vec2(16263.f, 1055.f));
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"DUMMY_MAGMA", L"texture\\Magma.png");
}

CDummy_Magma::~CDummy_Magma()
{
}

void CDummy_Magma::render()
{
	Vec2 vRenderPos = GetRenderPos();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
		, (int)vRenderPos.x
		, (int)vRenderPos.y
		, m_Img->GetWidth(), m_Img->GetHeight()
		, m_Img->GetDC()
		, 0, 0
		, m_Img->GetWidth(), m_Img->GetHeight(), bf);
}