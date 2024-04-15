#include "pch.h"
#include "CBoss_Enter.h"
#include "CCollisionMgr.h"

#include "CSoundMgr.h"
#include "CSound.h"


CBoss_Enter::CBoss_Enter()
	: m_pBGM(nullptr)
{
}

CBoss_Enter::~CBoss_Enter()
{
}

void CBoss_Enter::Enter()
{
	Initialize();

	GetAnimator()->Play(L"ENTER", true);
}

void CBoss_Enter::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();
	Vec2 vCenterPos = GetBlackboardData<Vec2>(L"CenterPos");

	if (vCenterPos.y - vPos.y < 400.f)
	{
		vPos.x += -1.f * 70.f * DT;
		vPos.y -= 1.f * 150.f * DT;

		GetObj()->SetPos(vPos);
	}
	if (vCenterPos.y - vPos.y > 400.f)
	{
		GetRigidBody()->UseGravity(true);
		GetRigidBody()->SetMaxGravitySpeed(1000.f);
		CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::PLATFORM);
	}

	if (GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"IDLE");
	}
}

void CBoss_Enter::Exit()
{
	m_pBGM = CAssetMgr::GetInst()->LoadSound(L"BOSS", L"sound\\level\\Boss.wav");
	CSoundMgr::GetInst()->RegisterToBGM(m_pBGM);
	m_pBGM->SetVolume(20.f);
	m_pBGM->Play(true);

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_ATTACK, LAYER_TYPE::BOSS);
}