#include "pch.h"
#include "CPlatform.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"
#include "CRigidBody.h"

CPlatform::CPlatform()
{
	//SetScale(Vec2(500.f, 100.f));
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::CPlatform(const Vec2& _StartPos, const Vec2& _EndPos)
{
	SetPos(_StartPos);
	SetScale(_EndPos);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::CPlatform(Vec2 _Pos, Vec2 _Scale, LAYER_TYPE _type)
{
	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::~CPlatform()
{
}

void CPlatform::begin()
{
}

void CPlatform::tick()
{
	
}

void CPlatform::render()
{
	if (L"Test" == GetName())
	{
		USE_PEN(DC, PEN_TYPE::PEN_GREEN);
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		Rectangle(DC, (int)vPos.x, (int)vPos.y, (int)vScale.x, (int)vScale.y);
	}

	else
		return;
}

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		if(PrevPos.y < vPos.y - vScale.y * 0.5f
			&& vOtherObjPos.x + vOtherObjScale.x * 0.5f >= vPos.x - vScale.x * 0.5f
			&& vOtherObjPos.x - vOtherObjScale.x * 0.5f <= vPos.x + vScale.x * 0.5f)
		{ 
			pRB->SetGround(true);
			pRB->SetClimb(false);
		}

		else if (PrevPos.y > vPos.y - vScale.y * 0.5f
			&& vOtherObjPos.x + vOtherObjScale.x * 0.5f > vPos.x - vScale.x * 0.5f
			&& !pRB->IsGround())
		{
			_OtherObj->SetPos(Vec2((vPos.x - vScale.x * 0.5f) - vOtherObjScale.x * 0.5f, vOtherObjPos.y));
			pRB->SetClimb(true);
		}

		else if (PrevPos.y > vPos.y - vScale.y * 0.5f
			&& vOtherObjPos.x - vOtherObjScale.x * 0.5f < vPos.x + vScale.x * 0.5f
			&& !pRB->IsGround())
		{
			_OtherObj->SetPos(Vec2((vPos.x + vScale.x * 0.5f) + vOtherObjScale.x * 0.5f, vOtherObjPos.y));
			pRB->SetClimb(true);
		}
	}
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

	if (PrevPos.y > vPos.y - vScale.y * 0.5f
		&& vOtherObjPos.x - vOtherObjScale.x * 0.5f < vPos.x + vScale.x * 0.5f
		&& !pRB->IsGround())
	{
		_OtherObj->SetPos(Vec2((vPos.x - vScale.x * 0.5f) - vOtherObjScale.x * 0.5f, vOtherObjPos.y));
		pRB->SetClimb(true);
	}

	else if 
		(PrevPos.y > vPos.y - vScale.y * 0.5f
			&& vOtherObjPos.x - vOtherObjScale.x * 0.5f > vPos.x + vScale.x * 0.5f
		&& !pRB->IsGround())
	 {
		_OtherObj->SetPos(Vec2((vPos.x + vScale.x * 0.5f) + vOtherObjScale.x * 0.5f, vOtherObjPos.y));
		pRB->SetClimb(true);
	 }

	}
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Player" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

		if (pRB->IsGround() && pRB->IsWall())
		{
			pRB->SetClimb(false);
		}
		
		else if (!pRB->IsGround() && pRB->IsWall())
		{
			pRB->SetClimb(false);
		}

		else if (pRB->IsGround())
		{
			pRB->SetGround(true);
		}

		else if (pRB->IsGround() && !pRB->IsWall())
		{
			pRB->SetGround(false);
		}
	}
}
