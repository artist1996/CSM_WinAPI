#include "pch.h"
#include "CPlatform.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CFSM.h"

#include "CBoss.h"
#include "CEffect_MonsterDead.h"

CPlatform::CPlatform()
	: m_Boss(true)
	, m_ID(OBJ_ID::END)
{
	//SetScale(Vec2(500.f, 100.f));
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::CPlatform(const Vec2& _StartPos, const Vec2& _EndPos)
	: m_Boss(true)
	, m_ID(OBJ_ID::END)
{
	SetPos(_StartPos);
	SetScale(_EndPos);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform::CPlatform(Vec2 _Pos, Vec2 _Scale, LAYER_TYPE _type)
	: m_Boss(true)
	, m_ID(OBJ_ID::END)
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
	if (LAYER_TYPE::MONSTER == _OtherObj->GetLayerType())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		_OtherObj->SetPos(_OtherObj->GetPos().x, GetPos().y - GetScale().y * 0.5f);
		pRB->SetGround(true);
	}

	if (L"Mettool" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		_OtherObj->SetPos(_OtherObj->GetPos().x, GetPos().y - GetScale().y * 0.5f);
		pRB->SetGround(true);
		pRB->UseGravity(false);
	}

	if (LAYER_TYPE::BOSS == _OtherObj->GetLayerType())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		pRB->SetGround(true);
	}

	if (L"BattonBomb" == _OtherObj->GetName())
	{
		_OtherObj->Destroy();
		CEffect_MonsterDead* pEffect = new CEffect_MonsterDead(_OtherObj);
		pEffect->SetPos(Vec2(_OtherObj->GetPos().x, GetPos().y - GetScale().y * 0.5f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
	}

	if (L"ZERO" == _OtherObj->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		CFSM* pFSM = _OtherObj->GetComponent<CFSM>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();


		if (PrevPos.y> vPos.y - vScale.y * 0.5f
			&& pRB->IsGround())
		{
			pRB->SetBlock(true);
			pFSM->ChangeState(L"BLOCK");
			return;
		}
		
		if (_OtherObj->GetPrevPos().y - 10.f <= vPos.y - vScale.y * 0.5f)
		{

			pRB->SetGround(true);
			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, vPos.y - vScale.y * 0.5f));
			//pFSM->ChangeState(L"LANDING");
			return;
		}
			
		else if (_OtherObj->GetPos().y > vPos.y - vScale.y * 0.5f
			&& _OtherObj->GetPos().y - _OtherObj->GetScale().y * 0.5f < vPos.y + vScale.y * 0.5f
			&& _OtherObj->GetPos().x <= vPos.x - vScale.x * 0.5f
			&& _OtherObj->GetPos().x < vPos.x
			&& !pRB->IsGround())
		{
			pRB->SetWall(true);
			pFSM->ChangeState(L"WALL_ENTER");
			return;
		}
			
		else if (_OtherObj->GetPos().y > vPos.y - vScale.y * 0.5f
			&& _OtherObj->GetPos().y - _OtherObj->GetScale().y * 0.5f < vPos.y + vScale.y * 0.5f
			&& _OtherObj->GetPos().x >= vPos.x + vScale.x * 0.5f
			&& _OtherObj->GetPos().x > vPos.x
			&& !pRB->IsGround())
		{
			pRB->SetWall(true);
			pFSM->ChangeState(L"WALL_ENTER");
			return;
		}

		else if (_OtherObj->GetPos().y > vPos.y + vScale.y * 0.5f
			&& _OtherObj->GetPos().x > vPos.x - vPos.x * 0.5f
			&& _OtherObj->GetPos().x < vPos.x + vPos.x * 0.5f)
		{
			pRB->SetJump(false);
			pRB->SetCeiling(true);
			pRB->SetVelocityByGravity(Vec2(0.f, 1.f));
			pFSM->ChangeState(L"FALL");
			return;
		}
	}
}

void CPlatform::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Body Collider" == _OtherCollider->GetName())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		Vec2 PrevPos = _OtherObj->GetPrevPos();
		Vec2 vOtherObjPos = _OtherObj->GetPos();
		Vec2 vOtherObjScale = _OtherObj->GetScale();
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();

		if (pRB->IsGround() && !pRB->IsBlock())
		{
			_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, vPos.y - vScale.y * 0.5f));
		}

		if (!pRB->IsGround() && pRB->IsWall())
		{
			if (DIRECTION::RIGHT == _OtherObj->GetDirection())
			{
				_OtherObj->SetPos(Vec2((vPos.x - vScale.x * 0.5f) - 45.f, _OtherObj->GetPos().y));
			}

			else if (DIRECTION::LEFT == _OtherObj->GetDirection())
			{
				_OtherObj->SetPos(Vec2((vPos.x + vScale.x * 0.5f) + 45.f, _OtherObj->GetPos().y));
			}
		}
	}

	if (LAYER_TYPE::MONSTER == _OtherObj->GetLayerType())
	{
		CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
		_OtherObj->SetPos(_OtherObj->GetPos().x, GetPos().y - GetScale().y * 0.5f);
		pRB->SetGround(true);
	}
}

void CPlatform::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	CRigidBody* pRB = _OtherObj->GetComponent<CRigidBody>();
	if (nullptr == pRB)
		return;

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

		pRB->SetCeiling(false);
	}
}