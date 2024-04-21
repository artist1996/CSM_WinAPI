#include "pch.h"
#include "CPlayer_Attack.h"

#include "CLevelMgr.h"

#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CEffect_Saber.h"
#include "CSound.h"

CPlayer_Attack::CPlayer_Attack(CObj* _Owner, Vec2 _Pos, ATTACK_TYPE _Type)
	: m_Owner(_Owner)
	, m_eType(_Type)
	, m_Animator(nullptr)
	, m_Time(0.f)
{
	SetPos(_Pos);
	SetName(L"PLAYER_ATTACK");
	m_Collider = (CCollider*)AddComponent(new CCollider);

	m_pSound = CAssetMgr::GetInst()->LoadSound(L"SABER", L"sound\\saber\\SABER.wav");
	m_HitSound = CAssetMgr::GetInst()->LoadSound(L"SABER_HIT", L"sound\\saber\\SABER_HIT.wav");
	m_pSound->Play();
}

CPlayer_Attack::~CPlayer_Attack()
{
}

void CPlayer_Attack::tick()
{
	CObj::tick();

	if (ATTACK_TYPE::ATTACK01 == m_eType)
	{
		Attack_01();
	}

	else if(ATTACK_TYPE::ATTACK02 == m_eType)
	{
		Attack_02();
	}

	else if (ATTACK_TYPE::ATTACK03 == m_eType)
	{
		Attack_03();
	}
}

void CPlayer_Attack::Attack_01()
{
	if (nullptr == m_Animator)
	{
		return;
	}
	
	if (m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection()
			&& L"BLACK_ATTACK01_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection()
			&& L"BLACK_ATTACK01_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}

	else if (!m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection()
			&& L"ATTACK01_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection()
			&& L"ATTACK01_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}


	if (L"ATTACK01_RIGHT" == m_Animator->GetCurAnim()->GetName() 
		|| L"BLACK_ATTACK01_RIGHT" == m_Animator->GetCurAnim()->GetName())
	{
		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(0.f, -90.f));
			m_Collider->SetScale(Vec2(40.f, 40.f));
		}

		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(75.f, -90.f));
			m_Collider->SetScale(Vec2(90.f, 100.f));
		}

		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(90.f, -65.f));
			m_Collider->SetScale(Vec2(90.f, 125.f));
		}
		
		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(90.f, -45.f));
			m_Collider->SetScale(Vec2(90.f, 90.f));
		}

		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(90.f, -15.f));
			m_Collider->SetScale(Vec2(90.f, 30.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(75.f, -15.f));
			m_Collider->SetScale(Vec2(60.f, 30.f));
		}

		if (8 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(70.f, -15.f));
			m_Collider->SetScale(Vec2(55.f, 35.f));
		}

		if (9 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			Destroy();
		}

	}

	else if (L"ATTACK01_LEFT" == m_Animator->GetCurAnim()->GetName()
		|| L"BLACK_ATTACK01_LEFT" == m_Animator->GetCurAnim()->GetName())
	{
		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(0.f, -90.f));
			m_Collider->SetScale(Vec2(40.f, 40.f));
		}

		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-75.f, -90.f));
			m_Collider->SetScale(Vec2(90.f, 100.f));
		}

		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-90.f, -65.f));
			m_Collider->SetScale(Vec2(90.f, 125.f));
		}

		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-90.f, -45.f));
			m_Collider->SetScale(Vec2(90.f, 90.f));
		}

		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-90.f, -15.f));
			m_Collider->SetScale(Vec2(90.f, 30.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-75.f, -15.f));
			m_Collider->SetScale(Vec2(60.f, 30.f));
		}

		if (8 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-70.f, -15.f));
			m_Collider->SetScale(Vec2(55.f, 35.f));
		}

		if (9 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			Destroy();
		}
	}
}

void CPlayer_Attack::Attack_02()
{
	if (nullptr == m_Animator)
	{
		return;
	}

	if (m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection()
			&& L"BLACK_ATTACK02_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection()
			&& L"BLACK_ATTACK02_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}

	else if (!m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection()
			&& L"ATTACK02_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection()
			&& L"ATTACK02_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}

	if (L"ATTACK02_RIGHT" == m_Animator->GetCurAnim()->GetName()
		|| L"BLACK_ATTACK02_RIGHT" == m_Animator->GetCurAnim()->GetName())
	{
		if (0 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(20.f, -45.f));
			m_Collider->SetScale(Vec2(30.f, 30.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(60.f, -55.f));
			m_Collider->SetScale(Vec2(75.f, 30.f));
		}

		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(45.f, -55.f));
			m_Collider->SetScale(Vec2(190.f, 35.f));
		}

		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(40.f, -45.f));
			m_Collider->SetScale(Vec2(240.f, 35.f));
		}

		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-80.f, -45.f));
			m_Collider->SetScale(Vec2(60.f, 35.f));
		}

		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-80.f, -50.f));
			m_Collider->SetScale(Vec2(60.f, 30.f));
		}

		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-75.f, -55.f));
			m_Collider->SetScale(Vec2(50.f, 25.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-60.f, -55.f));
			m_Collider->SetScale(Vec2(30.f, 25.f));
		}

		if (8 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-60.f, -55.f));
			m_Collider->SetScale(Vec2(20.f, 15.f));
		}

		if (9 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			Destroy();
		}
	}

	else if (L"ATTACK02_LEFT" == m_Animator->GetCurAnim()->GetName()
	     || L"BLACK_ATTACK02_LEFT" == m_Animator->GetCurAnim()->GetName())
	{
		if (0 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-20.f, -45.f));
			m_Collider->SetScale(Vec2(30.f, 30.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-60.f, -55.f));
			m_Collider->SetScale(Vec2(75.f, 30.f));
		}

		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-45.f, -55.f));
			m_Collider->SetScale(Vec2(190.f, 35.f));
		}

		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-40.f, -45.f));
			m_Collider->SetScale(Vec2(240.f, 35.f));
		}

		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(80.f, -45.f));
			m_Collider->SetScale(Vec2(60.f, 35.f));
		}

		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(80.f, -50.f));
			m_Collider->SetScale(Vec2(60.f, 30.f));
		}

		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(75.f, -55.f));
			m_Collider->SetScale(Vec2(50.f, 25.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(60.f, -55.f));
			m_Collider->SetScale(Vec2(30.f, 25.f));
		}

		if (8 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(60.f, -55.f));
			m_Collider->SetScale(Vec2(20.f, 15.f));
		}

		if (9 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			Destroy();
		}
	}
}

void CPlayer_Attack::Attack_03()
{
	if (nullptr == m_Animator)
	{
		return;
	}

	if (m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection()
			&& L"BLACK_ATTACK03_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection()
			&& L"BLACK_ATTACK03_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}

	else if (!m_Owner->IsBlack())
	{
		if (DIRECTION::RIGHT == m_Owner->GetDirection()
			&& L"ATTACK03_RIGHT" != m_Animator->GetCurAnim()->GetName()
			|| L"BLACK_ATTACK03_RIGHT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}

		else if (DIRECTION::LEFT == m_Owner->GetDirection()
			&& L"ATTACK03_LEFT" != m_Animator->GetCurAnim()->GetName()
			|| L"BLACK_ATTACK03_LEFT" != m_Animator->GetCurAnim()->GetName())
		{
			Destroy();
			return;
		}
	}

	if (L"ATTACK03_RIGHT" == m_Animator->GetCurAnim()->GetName()
		|| L"BLACK_ATTACK03_RIGHT" == m_Animator->GetCurAnim()->GetName())
	{
		if (0 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-40.f, -100.f));
			m_Collider->SetScale(Vec2(50.f, 35.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-45.f, -85.f));
			m_Collider->SetScale(Vec2(50.f, 53.f));
		}

		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-20.f, -110.f));
			m_Collider->SetScale(Vec2(105.f, 50.f));
		}

		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(70.f, -85.f));
			m_Collider->SetScale(Vec2(190.f, 130.f));
		}

		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(88.f, -65.f));
			m_Collider->SetScale(Vec2(160.f, 160.f));
		}

		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(90.f, -55.f));
			m_Collider->SetScale(Vec2(160.f, 140.f));
		}

		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(90.f, -30.f));
			m_Collider->SetScale(Vec2(160.f, 85.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(55.f, -5.f));
			m_Collider->SetScale(Vec2(85.f, 55.f));
		}

		if (8 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(35.f, -3.f));
			m_Collider->SetScale(Vec2(55.f, 50.f));
		}

		if (9 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			Destroy();
		}
	}

	else if (L"ATTACK03_LEFT" == m_Animator->GetCurAnim()->GetName()
		|| L"BLACK_ATTACK03_LEFT" == m_Animator->GetCurAnim()->GetName())
	{
		if (0 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(40.f, -100.f));
			m_Collider->SetScale(Vec2(50.f, 35.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(45.f, -85.f));
			m_Collider->SetScale(Vec2(50.f, 53.f));
		}

		if (2 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(20.f, -110.f));
			m_Collider->SetScale(Vec2(105.f, 50.f));
		}

		if (3 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-70.f, -85.f));
			m_Collider->SetScale(Vec2(190.f, 130.f));
		}

		if (4 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-88.f, -65.f));
			m_Collider->SetScale(Vec2(160.f, 160.f));
		}

		if (5 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-90.f, -55.f));
			m_Collider->SetScale(Vec2(160.f, 140.f));
		}

		if (6 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-90.f, -30.f));
			m_Collider->SetScale(Vec2(160.f, 85.f));
		}

		if (7 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-55.f, -5.f));
			m_Collider->SetScale(Vec2(85.f, 55.f));
		}

		if (8 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(-35.f, -3.f));
			m_Collider->SetScale(Vec2(55.f, 50.f));
		}

		if (9 <= m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			Destroy();
		}
	}
}

void CPlayer_Attack::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	m_HitSound->Play();

	if (LAYER_TYPE::MONSTER == _OtherObj->GetLayerType()
		|| LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
		|| L"Meteor" == _OtherObj->GetName()
		|| L"Door" == _OtherObj->GetName())
	{
		if (ATTACK_TYPE::ATTACK02 == m_eType)
		{
			CEffect_Saber* pEffect = new CEffect_Saber(Vec2(m_Collider->GetFinalPos().x , m_Collider->GetFinalPos().y)
				, EFFECT_TYPE::EFFECT_TWO);
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);			
		}

		else
		{
			CEffect_Saber* pEffect = new CEffect_Saber(Vec2(m_Collider->GetFinalPos().x, m_Collider->GetFinalPos().y)
				, EFFECT_TYPE::EFFECT_ONE);
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
		}
	}
}

void CPlayer_Attack::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (m_eType == ATTACK_TYPE::ATTACK03)
	{
		m_Time += DT;
	}

	if (0.001f <= m_Time)
	{
		m_HitSound->Play();
		m_Time = 0.f;
	}
}
