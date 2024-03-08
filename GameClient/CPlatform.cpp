#include "pch.h"
#include "CPlatform.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CPlatformMap.h"

CPlatform::CPlatform()
{
	//SetScale(Vec2(500.f, 100.f));
	m_PlatMap = (CPlatformMap*)AddComponent(new CPlatformMap);
	//m_Collider->SetScale(GetScale());
}

CPlatform::CPlatform(Vec2 _StartPos, Vec2 _EndPos)
{
	SetPos(_StartPos);
	SetScale(_EndPos);
	//m_Collider = (CCollider*)AddComponent(new CCollider);
	//m_Collider->SetScale(GetScale());
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
	Rectangle(DC, (int)GetPos().x, (int)GetPos().y
		, (int)GetScale().x, (int)GetScale().y);
}

//void CPlatform::Clicked(Vec2 _vMousePos)
//{
//	_vMousePos = CCamera::GetInst()->GetRealPos(_vMousePos);
//
//	m_PlatInfo.StartPos = _vMousePos;
//}

//void CPlatform::ReleasedClicked(Vec2 _vMousePos)
//{
//	_vMousePos = CCamera::GetInst()->GetRealPos(_vMousePos);
//	m_PlatInfo.EndPos = _vMousePos;
//	m_vecPlatInfo.push_back(m_PlatInfo);
//
//	CPlatform* pPlat = new CPlatform;
//	pPlat->SetPos(m_PlatInfo.StartPos);
//	pPlat->SetScale(m_PlatInfo.EndPos);
//
//	m_vecPlat.push_back(pPlat);
//	m_vecPlatInfo.clear();
//}

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
			_OtherObj->SetPos(vOtherObjPos.x, vPos.y - vScale.y * 0.5f);
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
