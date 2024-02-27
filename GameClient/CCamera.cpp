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
	if (m_EffectList.empty())
		return;

	CAM_EFFECT_INFO& info = m_EffectList.front();

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)info.Alpha;
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
	
	while (true)
	{
		if (m_EffectList.empty())
			return;

		CAM_EFFECT_INFO& info = m_EffectList.front();
		info.Time += DT;

		if (info.Duration < info.Time)
		{
			m_EffectList.pop_front();
		}
		else
		{
			break;
		}
	}

	CAM_EFFECT_INFO& info = m_EffectList.front();

	if (CAM_EFFECT::FADE_IN == info.Effect)
	{
		info.Alpha = (1.f - (info.Time / info.Duration)) * 255.f;
	}
	else if (CAM_EFFECT::FADE_OUT == info.Effect)
	{
		info.Alpha = (info.Time / info.Duration) * 255.f;
	}
}

void CCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	CAM_EFFECT_INFO info = {};
	info.Time = 0.f;
	info.Effect = _Effect;
	info.Duration = _Duration;
	info.Alpha = 0.f;
	
	m_EffectList.push_back(info);
}
