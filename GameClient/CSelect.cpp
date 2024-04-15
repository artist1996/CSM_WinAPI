#include "pch.h"
#include "CSelect.h"

CSelect::CSelect()
{
	SetPos(Vec2(0.f, 0.f));
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"SELECT", L"texture\\Select\\Background_Select.png");
	SetImg(pTex);
}

CSelect::~CSelect()
{
}

void CSelect::render()
{
	Vec2 vPos = GetRenderPos();
	

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
			, (int)vPos.x, (int)vPos.y
			, GetImg()->GetWidth(), GetImg()->GetHeight()
			, GetImg()->GetDC()
			, 0, 0
			, GetImg()->GetWidth(), GetImg()->GetHeight(), bf);
}