#include "pch.h"
#include "CMonster.h"
#include "CLevelMgr.h"

#include "CCollider.h"
#include "CMissile.h"
#include "CFSM.h"
#include "CMonsterIDLE.h"
#include "CMonsterTrace.h"


CMonster::CMonster()
	: m_HP(5)
	, m_DetectRange(300.f)
	, m_Speed(100.f)
{
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_FSM = (CFSM*)AddComponent(new CFSM);
	m_Collider->SetScale(Vec2(120.f, 120.f));

	m_FSM->AddState(L"IDLE", new CMonsterIDLE);
	m_FSM->AddState(L"Trace", new CMonsterTrace);
}

CMonster::~CMonster()
{
}

void CMonster::begin()
{
	m_FSM->SetBlackboardData(L"DetectRange", DATA_TYPE::FLOAT, &m_DetectRange);
	m_FSM->SetBlackboardData(L"Speed", DATA_TYPE::FLOAT, &m_Speed);
	m_FSM->SetBlackboardData(L"Self", DATA_TYPE::OBJECT, this);
	
	CObj* pPlayer = CLevelMgr::GetInst()->FindObjectByName(L"Player");
	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pPlayer);

	m_FSM->ChangeState(L"IDLE");
}

void CMonster::tick()
{
}

void CMonster::render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Vec2 vRenderPos = GetRenderPos();

	Rectangle(DC, (int)(vRenderPos.x - vScale.x * 0.5f)
		, (int)(vRenderPos.y - vScale.y * 0.5f)
		, (int)(vRenderPos.x + vScale.x * 0.5f)
		, (int)(vRenderPos.y + vScale.y * 0.5f));
}

void CMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj
							, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Missile")
	{
		--m_HP;

		if (0 >= m_HP)
		{
			Destroy();
		}		
	}
}
