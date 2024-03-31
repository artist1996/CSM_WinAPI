#include "pch.h"
#include "CPlatform.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CFSM.h"

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

void CPlatform::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		CFSM* pFSM = _OtherObj->GetComponent<CFSM>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();


		if (PrevPos.y > vPos.y - vScale.y * 0.5f
			&& pRB->IsGround())
		{
			pRB->SetBlock(true);
			pFSM->ChangeState(L"BLOCK");
			return;
		}
		
		if (_OtherObj->GetPos().y - 1.f <= vPos.y - vScale.y * 0.5f)
		{
			pRB->SetGround(true);
			//pFSM->ChangeState(L"LANDING");
			return;
		}
			
		else if (_OtherObj->GetPos().y > vPos.y - vScale.y * 0.5f
			&& _OtherObj->GetPos().y < vPos.y + vScale.y * 0.5f
			&& _OtherObj->GetPos().x < vPos.x - vScale.x * 0.5f
			&& _OtherObj->GetPos().x < vPos.x
			&& !pRB->IsGround())
		{
			pRB->SetWall(true);
			pFSM->ChangeState(L"WALL_ENTER");
			return;
		}
			
		else if (_OtherObj->GetPos().y > vPos.y - vScale.y * 0.5f
			&& _OtherObj->GetPos().y < vPos.y + vScale.y * 0.5f
			&& _OtherObj->GetPos().x > vPos.x - vScale.x * 0.5f
			&& _OtherObj->GetPos().x > vPos.x
			&& !pRB->IsGround())
		{
			pRB->SetWall(true);
			pFSM->ChangeState(L"WALL_ENTER");
			return;
		}
	}
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();	
	}
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		CFSM* pFSM = _OtherObj->GetComponent<CFSM>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

		if (pRB->IsBlock())
		{
			pRB->SetGround(true);
			pRB->SetBlock(false);
			return;
		}

		if (pRB->IsWall())
		{
			pRB->SetGround(false);
			pRB->SetWall(false);
			return;
		}

		if (pRB->IsGround() && !pRB->IsWall() && !pRB->IsBlock())
		{
			pRB->SetGround(false);
			return;
		}
	}
}