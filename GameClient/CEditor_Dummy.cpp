#include "pch.h"
#include "CEditor_Dummy.h"
#include "CLevelMgr.h"
#include "CLevel.h"

CEditor_Dummy::CEditor_Dummy()
	: m_UI(nullptr)
	, m_Img(nullptr)
{
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	
	SpawnObject(pLevel, LAYER_TYPE::DUMMY, this);
}

CEditor_Dummy::~CEditor_Dummy()
{
}

void CEditor_Dummy::render()
{
	//CObj::render();

	if (nullptr == m_UI || nullptr == m_Img)
		return;

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	AlphaBlend(DC, (int)vPos.x - 25
				 , (int)vPos.y - 30
				 , m_Img->GetWidth(), m_Img->GetHeight()
				 , m_Img->GetDC()
				 , 0, 0
				 , m_Img->GetWidth(), m_Img->GetHeight(), bf);
}