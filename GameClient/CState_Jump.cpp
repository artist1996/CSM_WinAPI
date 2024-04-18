#include "pch.h"
#include "CState_Jump.h"

#include "CSound.h"

#include "CPlayerEffectMgr.h"

CState_Jump::CState_Jump()
	: m_Speed(0.f)
	, m_pSound(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"JUMP", L"sound\\zero\\JUMP.wav");
}

CState_Jump::~CState_Jump()
{
}

void CState_Jump::Enter()
{
	m_pSound->Play();
	Initialize();
	GetRigidBody()->Jump();

	if (CPlayerEffectMgr::GetInst()->GetActive())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			CPlayerEffectMgr::GetInst()->Play(L"JUMP_RIGHT", true);
		}

		else
		{
			CPlayerEffectMgr::GetInst()->Play(L"JUMP_LEFT", true);
		}
	}


	GetCollider()->SetScale(Vec2(90.f, 130.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -60.f));

	if (GetObj()->IsBlack())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_JUMP_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_JUMP_LEFT", false);
		}
		return;
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"JUMP_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"JUMP_LEFT", false);
		}
	}
}

void CState_Jump::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	if (KEY_PRESSED(KEY::RIGHT))
	{ 
		CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"JUMP_RIGHT");

		if (GetObj()->IsBlack())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_JUMP_RIGHT"));
			vPos += Vec2(1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
		}

		else if (!GetObj()->IsBlack())
		{
			GetObj()->SetDirection(DIRECTION::RIGHT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"JUMP_RIGHT"));
			vPos += Vec2(1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
		}
	}

	else if (KEY_PRESSED(KEY::LEFT))
	{
		CPlayerEffectMgr::GetInst()->ChangeCurAnim(L"JUMP_LEFT");

		if (GetObj()->IsBlack())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"BLACK_JUMP_LEFT"));
			vPos += Vec2(-1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
		}

		else if(!GetObj()->IsBlack())
		{
			GetObj()->SetDirection(DIRECTION::LEFT);
			GetAnimator()->SetCurAnim(GetAnimator()->FindAnimation(L"JUMP_LEFT"));
			vPos += Vec2(-1.f, 0.f) * GetObj()->GetSpeed() * DT;
			GetObj()->SetPos(vPos);
		}
	}

	if (KEY_PRESSED(KEY::X))
	{
		if (GetAnimator()->GetCurAnim()->IsFinish())
		{
			GetFSM()->ChangeState(L"FALL");
			return;
		}
	}
	
	else if (KEY_RELEASED(KEY::X))
	{
		GetRigidBody()->SetVelocityByGravity(Vec2(0.f, 1.f));
		GetFSM()->ChangeState(L"FALL");
		return;
	}

	if (!GetAnimator()->GetCurAnim()->IsFinish() && KEY_TAP(KEY::C))
	{
		GetFSM()->ChangeState(L"RAKUOUHA");
		return;
	}
}

void CState_Jump::Exit()
{
}