#include "pch.h"
#include "CBoss_Destroy.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CEffect_Destroy.h"

#include "CSound.h"


CBoss_Destroy::CBoss_Destroy()
	: m_Time(0.f)
	, m_DestroyTime(0.f)
	, m_SoundTime(0.f)
	, m_CameraEvent(true)
	, m_pSound(nullptr)
	, m_pSound2(nullptr)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"DESTROY_BOSS", L"sound\\bomb\\Destroy3.wav");
	m_pSound2 = CAssetMgr::GetInst()->LoadSound(L"DESTROY2_BOSS", L"sound\\bomb\\Destroy2.wav");
}

CBoss_Destroy::~CBoss_Destroy()
{
}

void CBoss_Destroy::Enter()
{
	Initialize();
	
	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DESTROY_RIGHT", true);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DESTROY_LEFT", true);
	}
	GetRigidBody()->UseGravity(false);
	CCollisionMgr::GetInst()->CollisionUnCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS);
	CCollisionMgr::GetInst()->CollisionUnCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS_ATTACK);
	m_pSound->Play();
}

void CBoss_Destroy::FinalTick()
{
	m_Time += DT;
	m_SoundTime += DT;
	m_DestroyTime += DT;

	if (0.5f <= m_SoundTime)
	{
		m_pSound->Play();
		m_SoundTime = 0.f;
	}

	if (0.1f <= m_Time)
	{
		// Destroy Effect
		CEffect_Destroy* pEffect = new CEffect_Destroy(GetObj());
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
		m_Time = 0.f;
	}

	if (3.f <= m_DestroyTime && m_CameraEvent)
	{
		CCamera::GetInst()->SetDestroyBoss(true);
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 4.f);
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 4.f);
		m_CameraEvent = false;
	}

	if (7.f <= m_DestroyTime)
	{
		// Dead State ÀüÈ¯
		GetFSM()->ChangeState(L"DEAD");
	}
}

void CBoss_Destroy::Exit()
{
	m_pSound2->Play();
}