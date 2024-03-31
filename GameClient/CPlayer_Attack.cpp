#include "pch.h"
#include "CPlayer_Attack.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer_Attack::CPlayer_Attack(CObj* _Owner, Vec2 _Pos, ATTACK_TYPE _Type)
	: m_Owner(_Owner)
	, m_eType(_Type)
{
	SetPos(_Pos);

	m_Collider = (CCollider*)AddComponent(new CCollider);
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
	
	if (DIRECTION::RIGHT == m_Owner->GetDirection() && L"ATTACK01_RIGHT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}

	else if (DIRECTION::LEFT == m_Owner->GetDirection() && L"ATTACK01_LEFT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}

	if (L"ATTACK01_RIGHT" == m_Animator->GetCurAnim()->GetName())
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

	else if (L"ATTACK01_LEFT" == m_Animator->GetCurAnim()->GetName())
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

	if (DIRECTION::RIGHT == m_Owner->GetDirection() && L"ATTACK02_RIGHT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}

	else if (DIRECTION::LEFT == m_Owner->GetDirection() && L"ATTACK02_LEFT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}

	if (L"ATTACK02_RIGHT" == m_Animator->GetCurAnim()->GetName())
	{
		if (0 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(20.f, -45.f));
			m_Collider->SetScale(Vec2(30.f, 30.f));
		}

		if (1 == m_Animator->GetCurAnim()->GetCurFrameIdx())
		{
			m_Collider->SetOffsetPos(Vec2(60.f,-55.f));
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

	else if (L"ATTACK02_LEFT" == m_Animator->GetCurAnim()->GetName())
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

	if (DIRECTION::RIGHT == m_Owner->GetDirection() && L"ATTACK03_RIGHT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}

	else if (DIRECTION::LEFT == m_Owner->GetDirection() && L"ATTACK03_LEFT" != m_Animator->GetCurAnim()->GetName())
	{
		Destroy();
		return;
	}

	if (L"ATTACK03_RIGHT" == m_Animator->GetCurAnim()->GetName())
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

	else if (L"ATTACK03_LEFT" == m_Animator->GetCurAnim()->GetName())
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