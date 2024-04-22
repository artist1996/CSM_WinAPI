#include "pch.h"
#include "CPlatform_Death.h"

#include "CLevelMgr.h"
#include "CHUD_Player.h"

#include "CCollider.h"
#include "CFSM.h"

CPlatform_Death::CPlatform_Death()
	: m_ID(OBJ_ID::END)
	, m_Range(0.f)
	, m_Collider(nullptr)
{
}

CPlatform_Death::CPlatform_Death(Vec2 _Pos, Vec2 _Scale)
	: m_ID(OBJ_ID::DEATH)
	, m_Range(0.f)
	, m_Collider(nullptr)
{
	SetHp(0);
	SetPos(_Pos);
	SetScale(_Scale);
	
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform_Death::~CPlatform_Death()
{
}

void CPlatform_Death::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName()
		&& L"HitBox" == _OtherCollider->GetName()
		&& !_OtherObj->IsAlways())
	{
		// Dead
		CFSM* pFSM = _OtherObj->GetComponent<CFSM>();

		pFSM->ChangeState(L"DEAD");
		_OtherObj->MinusLife();
		return;
	}
}