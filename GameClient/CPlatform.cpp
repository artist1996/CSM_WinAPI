#include "pch.h"
#include "CPlatform.h"
#include "CCollider.h"
#include "CRigidBody.h"

CPlatform::CPlatform()
{
	SetScale(Vec2(500.f, 100.f));
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::~CPlatform()
{
}

void CPlatform::tick()
{
}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OhterCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(true);
	}
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(false);
	}
}