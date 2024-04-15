#include "pch.h"
#include "CBoss_Hadouken.h"

#include "CLevelMgr.h"

#include "CAnimation.h"

#include "CAttack_Hadouken.h"
#include "CSound.h"

CBoss_Hadouken::CBoss_Hadouken()
	: m_pSound(nullptr)
	, m_Spawn(true)
	, m_Spawn2(true)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"HADOUKEN", L"sound\\boss\\HADOUKEN.wav");
}

CBoss_Hadouken::~CBoss_Hadouken()
{
}

void CBoss_Hadouken::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"HADOUKEN_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"HADOUKEN_LEFT", false);
	}
}

void CBoss_Hadouken::FinalTick()
{
	if (1 == GetAnimator()->GetCurAnim()->GetCurFrameIdx())
	{
		// ÆÄµ¿Åº
		if (m_Spawn)
		{
			CAttack_Hadouken* pAttack = new CAttack_Hadouken(GetObj(),Vec2(GetObj()->GetPos().x, GetObj()->GetPos().y - 50.f));
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_ATTACK, pAttack);
			m_Spawn = false;
			m_pSound->Play();
		}
	}

	if (3 == GetAnimator()->GetCurAnim()->GetCurFrameIdx())
	{
		// ÆÄµ¿Åº
		if (m_Spawn2)
		{
			CAttack_Hadouken* pAttack = new CAttack_Hadouken(GetObj(), GetObj()->GetPos());
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_ATTACK, pAttack);
			m_Spawn2 = false;
			m_pSound->Play();
		}
	}

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"IDLE");
	}
}

void CBoss_Hadouken::Exit()
{
	m_Spawn = true;
	m_Spawn2 = true;
}