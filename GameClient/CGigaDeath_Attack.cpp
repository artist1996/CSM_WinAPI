#include "pch.h"
#include "CGigaDeath_Attack.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAttack_GigaDeath.h"


CGigaDeath_Attack::CGigaDeath_Attack()
	: m_Count(0)
{
}

CGigaDeath_Attack::~CGigaDeath_Attack()
{
}

void CGigaDeath_Attack::Enter()
{
	Vec2 vPos = GetObj()->GetPos();

	switch (m_Count)
	{
		case 0:
		{
			CAttack_GigaDeath* pAttack = new CAttack_GigaDeath(Vec2(vPos.x - 100.f, vPos.y - 30.f), Vec2(80.f, 50.f));
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_MISSILE, pAttack);
			++m_Count;
		}
			break;
		case 1:
		{
			CAttack_GigaDeath* pAttack = new CAttack_GigaDeath(Vec2(vPos.x - 100.f, vPos.y - 80.f), Vec2(80.f, 50.f));
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_MISSILE, pAttack);
			++m_Count;
		}
			break;
	}
}

void CGigaDeath_Attack::FinalTick()
{
	GetFSM()->ChangeState(L"IDLE");
}

void CGigaDeath_Attack::Exit()
{
	if (2 <= m_Count)
	{
		m_Count = 0;
	}
}