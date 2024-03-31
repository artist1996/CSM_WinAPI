#include "pch.h"
#include "CLine.h"
#include "CCollider.h"
#include "CRigidBody.h"

CLine::CLine()
	: m_Collider(nullptr)
{
}

CLine::CLine(Vec2 _StartPos, Vec2 _EndPos)
	: m_Collider(nullptr)
{
	SetPos(_StartPos);
	SetScale(_EndPos);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CLine::~CLine()
{
}

void CLine::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(true);
	}
}

void CLine::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	Vec2 vStart = GetPos();
	Vec2 vEnd = GetScale();
	Vec2 OtherPos = _OtherObj->GetPos();
	Vec2 OtherScale = _OtherObj->GetScale();
	Vec2 OtherObjPrevPos = _OtherObj->GetPrevPos();
	float M = 0.f;
	float B = 0.f;

	CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
	
	if (pRB->IsGround())
	{
		M = (vEnd.y - vStart.y) / (vEnd.x - vStart.x);

		B = vStart.y - (M * vStart.x);

		float LineY = M * OtherPos.x + B;

		if (_OtherObj->GetPos().y <= LineY)
		{
			_OtherObj->SetPos(_OtherObj->GetPos().x, LineY);
		}

		else if (_OtherObj->GetPos().y >= LineY)
		{
			_OtherObj->SetPos(_OtherObj->GetPos().x, LineY);
		}
	}
}

void CLine::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
	pRB->SetGround(false);
}