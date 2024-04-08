#include "pch.h"
#include "CMonster.h"
#include "CLevelMgr.h"

#include "CCollider.h"
#include "CMissile.h"
#include "CFSM.h"
#include "CRigidBody.h"
#include "CMonsterIDLE.h"
#include "CMonsterTrace.h"

#include "CEffect_MonsterDead.h"

CMonster::CMonster()
	: m_HP(0)
	, m_DetectRange(0.f)
	, m_Speed(0.f)
	, m_Time(0.f)
{
}

CMonster::CMonster(Vec2 _Pos, Vec2 _Scale)
	: m_HP(0)
	, m_DetectRange(0.f)
	, m_Speed(0.f)
	, m_Time(0.f)
{
	SetPos(_Pos);
	SetScale(_Scale);
}

CMonster::~CMonster()
{
}

void CMonster::begin()
{
	CObj::begin();
	CObj* pPlayer = CLevelMgr::GetInst()->FindObjectByName(L"Player");
}

void CMonster::tick()
{
	CObj::tick();

	if (0 >= m_HP)
	{
		Destroy();
		CEffect_MonsterDead* pEffect = new CEffect_MonsterDead(this);
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
	}

	if (IsHit())
	{
		m_Time += DT;
	}

	if (0.2f <= m_Time)
	{
		SetHit(false);
		m_Time = 0.f;
	}
}

void CMonster::render()
{
	CObj::render();
}

void CMonster::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj
							, CCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"PLAYER_ATTACK")
	{
		--m_HP;
		SetHit(true);
	}
}
