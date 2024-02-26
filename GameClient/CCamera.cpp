#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_Owner(nullptr)
	, m_FadeTex(nullptr)
	, m_CamSpeed(400.f)
	, m_Duration(0.f)
	, m_Time(0.f)
	, m_Alpha(0.f)
{}

CCamera::~CCamera()
{}

void CCamera::init()
{	
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_LookAt = Vec2(vResol.x / 2.f, vResol.y / 2.f);

	m_FadeTex = CAssetMgr::GetInst()->CreateTexture(L"CameraEffect", (UINT)vResol.x, (UINT)vResol.y);
}

void CCamera::tick()
{
	Move();
	
	CameraEffect();

	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt -  Vec2(vResol.x / 2.f, vResol.y / 2.f);
}

void CCamera::render()
{
	if (0.f >= m_Alpha)
		return;

	if (m_Alpha >= 255.f)
		return;

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)m_Alpha;
	bf.AlphaFormat = 0;

	AlphaBlend(DC
			   , 0, 0
			   , m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
			   , m_FadeTex->GetDC()
			   , 0, 0
			   , m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
			   , bf);
}

void CCamera::Move()
{
	if (nullptr != m_Owner)
	{
		m_LookAt.x = m_Owner->GetPos().x;
	}
}

void CCamera::CameraEffect()
{
	if (CAM_EFFECT::NONE == m_Effect)
		return;

	m_Time += DT;

	if (m_Time >= m_Duration)
	{
		m_Effect = CAM_EFFECT::NONE;
	}

	if (CAM_EFFECT::FADE_IN == m_Effect)
	{
		m_Alpha = (1.f - (m_Time / m_Duration)) * 255.f;
	}

	else if (CAM_EFFECT::FADE_OUT == m_Effect)
	{
		m_Alpha = (m_Time / m_Duration) * 255.f;
	}
}

void CCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	m_Effect = _Effect;
	m_Duration = _Duration;
	m_Time = 0.f;
}
