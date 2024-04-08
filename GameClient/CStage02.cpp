#include "pch.h"
#include "CStage02.h"

CStage02::CStage02()
{
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"VOLCANO_02", L"texture\\Volcano_02.png");
	SetImg(pTex);
	SetScale((float)pTex->GetWidth(), (float)pTex->GetHeight());
}

CStage02::~CStage02()
{
}

void CStage02::render()
{
	Vec2 vPos = GetRenderPos();
	StretchBlt(DC, (int)vPos.x, (int)vPos.y
		, GetImg()->GetWidth() * 3, (UINT)(GetImg()->GetHeight() * 2.5)
		, GetImg()->GetDC(), 0, 0, GetImg()->GetWidth()
		, GetImg()->GetHeight()
		, SRCCOPY);
}