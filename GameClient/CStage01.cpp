#include "pch.h"
#include "CStage01.h"
#include "CAssetMgr.h"
#include "CTexture.h"

CStage01::CStage01()
{
	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"VOLCANO_01", L"texture\\Volcano_01.png");
	SetImg(pTex);
	SetScale((float)pTex->GetWidth(), (float)pTex->GetHeight());
}

CStage01::~CStage01()
{
}

void CStage01::render()
{
	CBackGround::render();
}