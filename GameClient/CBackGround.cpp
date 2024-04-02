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

	StretchBlt(DC, (int)vPos.x, (int)vPos.y
			, GetImg()->GetWidth() * 3, (UINT)(GetImg()->GetHeight() * 2)
			, GetImg()->GetDC(), 0, 0, GetImg()->GetWidth()
			, GetImg()->GetHeight()
			, SRCCOPY);
}