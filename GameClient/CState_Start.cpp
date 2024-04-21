#include "pch.h"
#include "CState_Start.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CSound.h"

CState_Start::CState_Start()
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"START", L"sound\\zero\\START.wav");
}

CState_Start::~CState_Start()
{
}

void CState_Start::Enter()
{
	Initialize();
	GetAnimator()->Play(L"START", false);
	m_pSound->Play();
	GetRigidBody()->UseGravity(true);
}

void CState_Start::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();

	GetCollider()->SetScale(Vec2(90.f, 105.f));
	GetCollider()->SetOffsetPos(Vec2(0.f, -50.f));

	vPos += Vec2(0.f, 1.f) * 200.f * DT;
	GetObj()->SetPos(vPos);
	
	if (GetRigidBody()->IsGround())
	{
		GetFSM()->ChangeState(L"ENTER");
	}
}

void CState_Start::Exit()
{
}