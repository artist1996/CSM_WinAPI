#include "pch.h"
#include "CState_Dead.h"

#include "CSound.h"

#include "CPlayerEffectMgr.h"

CState_Dead::CState_Dead()
	: m_pSound(nullptr)
	, m_CamEvent(false)
	, m_First(true)
	, m_Dead(false)
	, m_Time(0.f)
	, m_FadeTime(0.f)
{
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"ZERO_DEAD", L"sound\\zero\\DEAD.wav");
}

CState_Dead::~CState_Dead()
{
}

void CState_Dead::Enter()
{
	m_pSound->Play();
	Initialize();
	GetRigidBody()->UseGravity(false);
	CPlayerEffectMgr::GetInst()->SetActive(false);

	if (DIRECTION::RIGHT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DEAD_RIGHT", false);
	}

	else if (DIRECTION::LEFT == GetObj()->GetDirection())
	{
		GetAnimator()->Play(L"DEAD_LEFT", false);
	}
}

void CState_Dead::FinalTick()
{
	if (m_First)
	{
		m_Time += DT;
	}

	if (m_Dead)
	{
		m_FadeTime += DT;
	}

	if (2.f <= m_Time)
	{
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 2.f);
		CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 2.f);
		
		m_CamEvent = true;
		m_First = false;
		m_Dead = true;
		m_Time = 0.f;
	}

	if (m_CamEvent)
	{
		CCamera::GetInst()->SetOwner(nullptr);
		m_CamEvent = false;
	}

	if (2.f <= m_FadeTime)
	{
		CCamera::GetInst()->SetCameraLookAt(Vec2(GetObj()->GetRespawnPos().x, CCamera::GetInst()->GetRespawnPos()));
	}

	if (4.f <= m_FadeTime)
	{
		m_Dead = false;
		//CCamera::GetInst()->SetCameraLookAt(Vec2(GetObj()->GetRespawnPos().x, CCamera::GetInst()->GetRespawnPos()));
		GetObj()->SetPos(GetObj()->GetRespawnPos());
		GetFSM()->ChangeState(L"START");
	}

}

void CState_Dead::Exit()
{
	m_First = true;
	m_CamEvent = false;
	m_Dead = false;
	m_Time = 0.f;
	m_FadeTime = 0.f;
}