#include "pch.h"
#include "CSpawner_Meteor.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CTrap_Meteor.h"

CSpawner_Meteor::CSpawner_Meteor()
	: m_Owner(nullptr)
	, m_ID(OBJ_ID::END)
	, m_Time(0.f)
	, m_Spawn(false)
{
}

CSpawner_Meteor::CSpawner_Meteor(CObj* _Owner, OBJ_ID _ID)
	: m_Owner(_Owner)
	, m_ID(_ID)
	, m_Time(0.f)
	, m_Spawn(false)
{
	SetPos(static_cast<CTrap_Meteor*>(m_Owner)->GetStartPos());
}

CSpawner_Meteor::~CSpawner_Meteor()
{
}

void CSpawner_Meteor::tick()
{
	Vec2 vPos = GetPos();

	if (m_Owner->IsDead())
	{
		m_Spawn = true;
	}

	if (m_Spawn)
	{
		m_Time += DT;
	}

	if (2.f <= m_Time)
	{
		CTrap_Meteor* pMeteor = new CTrap_Meteor(vPos, m_ID);
		m_Owner = pMeteor;
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::TRAP, pMeteor);
		m_Time = 0.f;
		m_Spawn = false;
	}
}