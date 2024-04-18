#include "pch.h"
#include "CEditor_RenderDummy.h"

CEditor_RenderDummy::CEditor_RenderDummy()
	: m_Img(nullptr)
	, m_ID(OBJ_ID::END)
	, m_HP(0)
	, m_DetectRange(0.f)
{
}

CEditor_RenderDummy::CEditor_RenderDummy(Vec2 _Pos, Vec2 _Scale, OBJ_ID _ID, int _HP, float _DetectRange)
	: m_ID(_ID)
	, m_HP(_HP)
	, m_DetectRange(_DetectRange)
	, m_Img(nullptr)
{
	// Info
	SetPos(_Pos);
	SetScale(_Scale);

	// Texture
	if (OBJ_ID::BATTON == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Batton", L"texture\\render_dummy\\dummy_batton.png");
	}

	else if (OBJ_ID::METTOOL == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Mettool", L"texture\\render_dummy\\dummy_mettool.png");
	}

	else if (OBJ_ID::GIGADEATH == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"GigaDeath", L"texture\\render_dummy\\dummy_gigadeath.png");
	}

	else if (OBJ_ID::RAIDEN == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Raiden", L"texture\\render_dummy\\dummy_raiden.png");
	}

	else if (OBJ_ID::METEOR_UP == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"MeteorUp", L"texture\\render_dummy\\dummy_meteorup.png");
	}

	else if (OBJ_ID::METEOR_DOWN == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"MeteorDown", L"texture\\render_dummy\\dummy_meteordown.png");
	}

	else if (OBJ_ID::METEOR_DIAGONAL == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"MeteorDiagonal", L"texture\\render_dummy\\dummy_meteordiagonal.png");
	}

	else if (OBJ_ID::METEOR_LEFT == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"MeteorLeft", L"texture\\render_dummy\\dummy_meteorleft.png");
	}

	else if (OBJ_ID::METEOR_RIGHT == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"MeteorRight", L"texture\\render_dummy\\dummy_meteorright.png");
	}

	else if (OBJ_ID::ERUPTION == m_ID)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"EruptionRender", L"texture\\render_dummy\\dummy_eruption.png");
	}
}

CEditor_RenderDummy::~CEditor_RenderDummy()
{
}

void CEditor_RenderDummy::render()
{
	CObj::render();

	if (nullptr == m_Img)
		return;
	
	Vec2 vRenderPos = GetRenderPos();
	
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)(vRenderPos.x - m_Img->GetWidth() * 0.5f)
				 , (int)(vRenderPos.y - m_Img->GetHeight())
				 , m_Img->GetWidth(), m_Img->GetHeight()
				 , m_Img->GetDC()
				 , 0 ,0
				 , m_Img->GetWidth(), m_Img->GetHeight(), bf);
}