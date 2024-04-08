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
	
	// RIGHT
	m_Animator->LoadAnimation(L"animation\\afterimage\\right\\JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\right\\DASH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\afterimage\\right\\FALL_RIGHT.anim");
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
	if (m_bActive)
	{
		Vec2 vPos = GetPos();
		CObj* pObj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");
		Vec2 vDir = pObj->GetPos() - GetPos();


		float fDist = abs(pObj->GetPos().x - vPos.x);
		if (0.1f > fDist)
		{
			m_bActive = false;
		}

		if (!vDir.IsZero())
		{
			vDir.Normalize();
			vPos += (vDir * 600.f * DT);
			
			SetPos(vPos);
		}
	}

	else
	{
		SetDirection(m_Owner->GetDirection());
		if (DIRECTION::RIGHT == GetDirection())
		{
			SetPos(Vec2(m_Owner->GetPos().x - 20.f, m_Owner->GetPos().y));
		}

		else if (DIRECTION::LEFT == GetDirection())
		{
			SetPos(Vec2(m_Owner->GetPos().x + 20.f, m_Owner->GetPos().y));
		}
	}
}

void CAfterImage::render()
{
	if (m_bActive)
	{
		m_Animator->render();
	}
}