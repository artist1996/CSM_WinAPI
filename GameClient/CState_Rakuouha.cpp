#include "pch.h"
#include "CState_Rakuouha.h"
#include "CPlayer.h"

CState_Rakuouha::CState_Rakuouha()
{
}

CState_Rakuouha::~CState_Rakuouha()
{
}

void CState_Rakuouha::Enter()
{
	Initialize();

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"RAKUOUHA_RIGHT", false);
		dynamic_cast<CPlayer*>(GetObj())->CreateJumpAttack();
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"RAKUOUHA_LEFT", false);
		dynamic_cast<CPlayer*>(GetObj())->CreateJumpAttack();
	}
}

void CState_Rakuouha::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (KEY_TAP(KEY::RIGHT))
	{
		GetObj()->SetDirection(DIRECTION::RIGHT);
		GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"RAKUOUHA_RIGHT"));
	}

	else if (KEY_TAP(KEY::LEFT))
	{
		GetObj()->SetDirection(DIRECTION::LEFT);
		GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"RAKUOUHA_LEFT"));
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos += Vec2(1.f, 0.f) * 400.f * DT;
		GetObj()->SetPos(vPos);
	}

	else if (KEY_PRESSED(KEY::LEFT))
	{
		vPos += Vec2(-1.f, 0.f) * 400.f * DT;
		GetObj()->SetPos(vPos);
	}

	if (GetAnimator()->GetCurAnim()->IsFinish())
	{
		GetFSM()->ChangeState(L"FASTFALL");
		return;
	}

	if (GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"LANDING");
		return;
	}
}

void CState_Rakuouha::Exit()
{
}