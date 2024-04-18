#include "pch.h"
#include "CAfterImage.h"

#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CAfterImage::CAfterImage(CObj* _Owner, Vec2 _Pos)
	: m_Owner(_Owner)
	, m_Animator(nullptr)
	, m_bActive(false)
	, m_bRender(false)
	, m_Time(0.f)
	, m_RenderTime(0.f)
{
	// Info
	SetName(L"Shadow");
	SetPos(_Pos);
	SetDirection(m_Owner->GetDirection());
	SetSpeed(m_Owner->GetSpeed() - 20.f);

	// Component
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// LEFT
	m_Animator->LoadAnimation(L"animation\\afterimage\\left\\JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\left\\DASH_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\left\\FALL_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\left\\WALLKICK_LEFT.anim");
	
	// RIGHT
	m_Animator->LoadAnimation(L"animation\\afterimage\\right\\JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\right\\DASH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\right\\FALL_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\right\\WALLKICK_RIGHT.anim");

	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"BLACKAfterImage_Left", L"texture\\BLACK_AFTERIMAGE_LEFT.png");
	pTex = CAssetMgr::GetInst()->LoadTexture(L"BLACKAfterImage_Right", L"texture\\BLACK_AFTERIMAGE_RIGHT.png");
}

CAfterImage::~CAfterImage()
{
}

void CAfterImage::Play(const wstring& _strName, bool _Play)
{
	m_Animator->Play(_strName, _Play);
}

void CAfterImage::tick()
{
	CObj::tick();

	if (!m_bActive)
	{
		m_RenderTime = 0.f;
		m_bRender = false;
	}
	
	if (m_bActive)
	{
		m_bRender = true;
		m_RenderTime += DT;
	}

	m_Time += DT;

	if (0.05f <= m_Time)
	{
		SetPos(m_Owner->GetPrevPos());
		m_Time = 0.f;
	}

	if (0.03f <= m_RenderTime)
	{
		//m_bRender = false;
		m_RenderTime = 0.f;
	}
}

void CAfterImage::render()
{
	if (m_bRender)
	{
		m_Animator->render();
	}
}