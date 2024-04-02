#include "pch.h"
#include "CMettool_Attack.h"
#include "CAnimation.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMissile.h"

CMettool_Attack::CMettool_Attack()
	: m_Change(false)
{
}

CMettool_Attack::~CMettool_Attack()
{
}

void CMettool_Attack::Enter()
{
	Initialize();

	CObj* pTarget = GetFSM()->GetBlackboardData<CObj*>(L"Target");
	Vec2 vPos = GetObj()->GetPos();
	


	float fDist = pTarget->GetPos().x -  vPos.x;

	if (0.f > fDist)
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		GetAnimator()->Play(L"ATTACK_LEFT", false);
	}

	else if (0.f < fDist)
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		GetAnimator()->Play(L"ATTACK_RIGHT", false);
	}

	dynamic_cast<CMettool_Attack*>(GetObj());
	m_Change = true;
}

void CMettool_Attack::FinalTick()
{
	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
		return;
	}

	CObj* pTarget = GetFSM()->GetBlackboardData<CObj*>(L"Target");
	Vec2 vPos = GetObj()->GetPos();

	
	if (m_Change)
	{
		CMissile* pMissile = new CMissile(vPos, Vec2(30.f, 30.f), GetObj());
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_MISSILE, pMissile);

		m_Change = false;
		return;
	}
}

void CMettool_Attack::Exit()
{
	m_Change = false;
}