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
		// �浹ü�� �����ϰ� �ִ� ������Ʈ�� �Ҽ� ���̾ �ڽ��� ��Ͻ�Ų��.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pLevel->RegisterCollider(this);

		// ��Ȱ��ȭ ���¸� ��Ͽɼ��� �����Ѵ�(������ �����Ӻ��� ����� ���� �ʴ´�.
		if (!m_Active)
		{
			m_bRegister = false;
		}
	}

	// ��Ȱ��ȭ ������ �浹ü�� DebugRender �� ��û���� �ʴ´�.
	if (!m_Active)
		return;

	
	if (0 != m_CollisionCount)
	{
		DrawDebugRect(PEN_TYPE::PEN_RED, m_FinalPos, m_Scale, 0.f);
	}

	else
	{
		DrawDebugRect(PEN_TYPE::PEN_GREEN, m_FinalPos, m_Scale, 0.f);
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