#include "pch.h"
#include "CCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CCollider::CCollider()
	: m_CollisionCount(0)
	, m_Active(true)
	, m_bRegister(true)
{
}

CCollider::CCollider(const CCollider& _Other)
	: CComponent(_Other)
	, m_CollisionCount(0)
	, m_Active(_Other.m_Active)
	, m_bRegister(_Other.m_bRegister)
{
}

CCollider::~CCollider()
{
}


void CCollider::finaltick()
{
	m_FinalPos = GetOwner()->GetPos() + m_OffsetPos;

	if (m_bRegister)
	{
		// 충돌체를 소유하고 있는 오브젝트의 소속 레이어에 자신을 등록시킨다.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);

		// 비활성화 상태면 등록옵션을 정지한다(다음번 프레임부터 등록이 되지 않는다.
		if (!m_Active)
		{
			m_bRegister = false;
		}
	}

	// 비활성화 상태의 충돌체는 DebugRender 를 요청하지 않는다.
	if (!m_Active)
		return;

	if (LAYER_TYPE::LINE == GetOwner()->GetLayerType())
	{
		if (0 != m_CollisionCount)
		{
			DrawDebugLine(PEN_TYPE::PEN_RED, m_FinalPos, m_Scale, 0.f);
		}

		else
		{
			DrawDebugLine(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
		}
	}

	else
	{
		if (0 != m_CollisionCount)
		{
			DrawDebugRect(PEN_TYPE::PEN_RED, m_FinalPos, m_Scale, 0.f);
		}

		else
		{
			DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
		}
	}
	
}

void CCollider::BeginOverlap(CCollider* _OtherCollider)
{
	m_CollisionCount++;

	GetOwner()->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void CCollider::OnOverlap(CCollider* _OtherCollider)
{
	GetOwner()->OnOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}

void CCollider::EndOverlap(CCollider* _OtherCollider)
{
	m_CollisionCount--;

	GetOwner()->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
}