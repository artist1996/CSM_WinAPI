#include "pch.h"
#include "CState_Victory.h"

#include "CAnimation.h"

#include "CSound.h"

CState_Victory::CState_Victory()
	: m_Time(0.f)
	, m_bAnimation(true)
	, m_Play(false)
	, m_Animator(nullptr)
	, m_bUP(false)
	, m_Victory(true)
	, m_Recall(true)
	, m_VictorySound(nullptr)
	, m_RecallSound(nullptr)
{
	m_VictorySound = CAssetMgr::GetInst()->LoadSound(L"VICTORY", L"sound\\zero\\VICTORY.wav");
	m_RecallSound = CAssetMgr::GetInst()->LoadSound(L"RECALL", L"sound\\zero\\RECALL.wav");
}

CState_Victory::~CState_Victory()
{
}

void CState_Victory::Enter()
{
	Initialize();

	if (GetObj()->IsBlack())
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_VICTORY_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"BLACK_VICTORY_LEFT", false);
		}
	}

	else
	{
		if (DIRECTION::RIGHT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"VICTORY_RIGHT", false);
		}

		else if (DIRECTION::LEFT == GetObj()->GetDirection())
		{
			GetAnimator()->Play(L"VICTORY_LEFT", false);
		}
	}

	GetRigidBody()->UseGravity(false);
	CCamera::GetInst()->SetOwner(nullptr);
}

void CState_Victory::FinalTick()
{
	Vec2 vPos = GetObj()->GetPos();
	
	if (m_Victory && 5 == GetAnimator()->GetCurAnim()->GetCurFrameIdx())
	{
		m_VictorySound->Play();
		m_Victory = false;
	}

	if (12 <= GetAnimator()->GetCurAnim()->GetCurFrameIdx())
	{
		if (m_Recall)
		{
			m_RecallSound->Play();
			m_Recall = false;
		}
		vPos += Vec2(0.f, -1.f) * 800.f * DT;
		GetObj()->SetPos(vPos);
	}
	
	if (abs(m_CenterPos.y - vPos.y) > 2000.f)
	{
		// 체인지 레벨
		ChangeLevel(LEVEL_TYPE::LOGO_START);
	}

}

void CState_Victory::Exit()
{
	m_Victory = true;
	m_Recall = true;
}