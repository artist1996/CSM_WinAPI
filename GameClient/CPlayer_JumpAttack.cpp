#include "pch.h"
#include "CPlayer_JumpAttack.h"
#include "CLevelMgr.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CAnimator.h"

#include "CEffect_Saber.h"

#include "CSound.h"

CPlayer_JumpAttack::CPlayer_JumpAttack()
	: m_Owner(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_pSound(nullptr)
	, m_HitSound(nullptr)
{
}

CPlayer_JumpAttack::CPlayer_JumpAttack(CObj* _Owner, CAnimator* _Animator, Vec2 _Pos)
	: m_Owner(_Owner)
	, m_Animator(_Animator)
	, m_Collider(nullptr)
	, m_pSound(nullptr)
	, m_HitSound(nullptr)
{
	SetName(L"PLAYER_JUMPATTACK");
	SetPos(_Pos);
	m_Collider = (CCollider*)AddComponent(new CCollider);

	m_pSound = CAssetMgr::GetInst()->LoadSound(L"SABER", L"sound\\saber\\SABER.wav");
	m_HitSound = CAssetMgr::GetInst()->LoadSound(L"SABER_HIT", L"sound\\saber\\SABER_HIT.wav");
	m_pSound->Play();
}

CPlayer_JumpAttack::~CPlayer_JumpAttack()
{
}

void CPlayer_JumpAttack::tick()
{
	CObj::tick();

	if (m_Animator->GetCurAnim()->IsFinish())
	{
		Destroy();
	}
	
	if (m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection() && L"BLACK_JUMPATTACK_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		if (DIRECTION::LEFT == m_Owner->GetDirection() && L"BLACK_JUMPATTACK_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}

	else if (!m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection() && L"RAKUOUHA_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		if (DIRECTION::LEFT == m_Owner->GetDirection() && L"RAKUOUHA_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}
	JumpAttack();

	Vec2 vPos = m_Owner->GetPos();
	
	
	SetPos(vPos);
}

void CPlayer_JumpAttack::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	m_HitSound->Play();

	if (LAYER_TYPE::MONSTER == _OtherObj->GetLayerType()
		|| LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
		|| L"Meteor" == _OtherObj->GetName()
		|| L"Door" == _OtherObj->GetName())
	{
		CEffect_Saber* pEffect = new CEffect_Saber(m_Collider->GetFinalPos(), EFFECT_TYPE::EFFECT_ONE);
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
	}
}

void CPlayer_JumpAttack::JumpAttack()
{
	if (m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection())
		{
			if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(0.f, -130.f));
				m_Collider->SetScale(Vec2(55.f, 30.f));
			}
			if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(55.f, -100.f));
				m_Collider->SetScale(Vec2(70.f, 70.f));
			}

			if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(50.f, -90.f));
				m_Collider->SetScale(Vec2(152.f, 110.f));
			}

			if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(45.f, -80.f));
				m_Collider->SetScale(Vec2(220.f, 122.f));
			}

			if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-50.f, -80.f));
				m_Collider->SetScale(Vec2(40.f, 60.f));
			}

			if (6 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				Destroy();
			}
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection())
		{
			if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(0.f, -130.f));
				m_Collider->SetScale(Vec2(55.f, 30.f));
			}
			if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-55.f, -100.f));
				m_Collider->SetScale(Vec2(70.f, 70.f));
			}

			if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-50.f, -90.f));
				m_Collider->SetScale(Vec2(152.f, 110.f));
			}

			if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-45.f, -80.f));
				m_Collider->SetScale(Vec2(220.f, 122.f));
			}

			if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(50.f, -80.f));
				m_Collider->SetScale(Vec2(40.f, 60.f));
			}

			if (6 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				Destroy();
			}
		}
	}

	else if (!m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection())
		{
			if (0 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(45.f, -130.f));
				m_Collider->SetScale(Vec2(125.f, 140.f));
			}

			if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(75.f, -110.f));
				m_Collider->SetScale(Vec2(105.f, 165.f));
			}

			if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(50.f, -40.f));
				m_Collider->SetScale(Vec2(150.f, 80.f));
			}
			if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(5.f, -20.f));
				m_Collider->SetScale(Vec2(125.f, 90.f));
			}
			if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-40.f, -30.f));
				m_Collider->SetScale(Vec2(120.f, 130.f));
			}
			if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-68.f, -70.f));
				m_Collider->SetScale(Vec2(105.f, 135.f));
			}
			if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-55.f, -150.f));
				m_Collider->SetScale(Vec2(145.f, 80.f));
			}
			if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-5.f, -150.f));
				m_Collider->SetScale(Vec2(125.f, 100.f));
			}

			if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx() && 0.025 <= m_Animator->GetCurAnim()->GetFrame(7).Duration)
			{
				Destroy();
			}
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection())
		{
			if (0 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-45.f, -130.f));
				m_Collider->SetScale(Vec2(125.f, 140.f));
			}

			if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-75.f, -110.f));
				m_Collider->SetScale(Vec2(105.f, 165.f));
			}

			if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-50.f, -40.f));
				m_Collider->SetScale(Vec2(150.f, 80.f));
			}
			if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(-5.f, -20.f));
				m_Collider->SetScale(Vec2(125.f, 90.f));
			}
			if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(40.f, -30.f));
				m_Collider->SetScale(Vec2(120.f, 130.f));
			}
			if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(68.f, -70.f));
				m_Collider->SetScale(Vec2(105.f, 135.f));
			}
			if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(55.f, -150.f));
				m_Collider->SetScale(Vec2(145.f, 80.f));
			}
			if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
			{
				m_Collider->SetOffsetPos(Vec2(5.f, -150.f));
				m_Collider->SetScale(Vec2(125.f, 100.f));
			}

			if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx() && 0.025 <= m_Animator->GetCurAnim()->GetFrame(7).Duration)
			{
				Destroy();
			}
		}
	}
}