#include "pch.h"
#include "CBoss_Enter.h"
#include "CCollisionMgr.h"


CBoss_Enter::CBoss_Enter()
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
		vPos.x += -1.f * 50.f * DT;
		vPos.y -= 1.f * 150.f * DT;

		GetObj()->SetPos(vPos);
	}
	if (vCenterPos.y - vPos.y > 400.f)
	{
		GetRigidBody()->UseGravity(true);
		CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::PLATFORM);
	}

	if (GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"IDLE");
	}
}

void CBoss_Enter::Exit()
{
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::BOSS);
}