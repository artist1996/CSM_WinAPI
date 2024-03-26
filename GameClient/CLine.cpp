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
}

void CLine::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	Vec2 vStart = GetPos();
	Vec2 vEnd = GetScale();
	Vec2 OtherPos = _OtherObj->GetPos();
	Vec2 OtherScale = _OtherObj->GetScale();
	Vec2 OtherObjPrevPos = _OtherObj->GetPrevPos();
	CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
	float M = 0.f;
	float B = 0.f;

	M = (vEnd.y - vStart.y) / (vEnd.x - vStart.x);

	B = vStart.y - (M * vStart.x);

	float PlayerY = OtherPos.y - OtherScale.y * 0.5f;

	float LineY = M * OtherPos.x + B;
	
	if (OtherPos.y >= LineY - 0.5f)
	{
		pRB->SetGround(true);
		_OtherObj->SetPos(OtherPos.x, LineY);
	}

	else if (OtherPos.y < LineY)
	{
		pRB->SetGround(false);
	}
}

void CLine::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(false);
	}
}