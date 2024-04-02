#include "pch.h"
#include "CForce.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CRigidBody.h"

CForce::CForce()
	: m_Force(0.f)
	, m_Range(0.f)
	, m_Time(0.f)
{
}

CForce::~CForce()
{
}

void CForce::tick()
{
	AddForce(LAYER_TYPE::MONSTER);
	AddForce(LAYER_TYPE::PLAYER);
	// �ð� ����
	m_Age += DT;
	DrawDebugCircle(PEN_TYPE::PEN_BLUE, GetPos(), Vec2(m_Range * 2.f, m_Range * 2.f), 0.f);
	
	if (m_Time < m_Age)
	{
		Destroy();
	}
}

void CForce::AddForce(LAYER_TYPE _Type)
{
	// ���� ������ ���ͼ� �ش� Ÿ���� Object���� �� �����´�.
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecObj = pLevel->GetObjects(_Type);
	
	
	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		// Force�� ���� �Ÿ��� Force�� Object�� �Ÿ����� ũ�ٸ� �浹 �ѰŴ�.
		float fDist = GetPos().GetDistance(vecObj[i]->GetPos());

		if (fDist <= m_Range)
		{
			// rigidbody ������Ʈ ���´�.
			CRigidBody* pComponent = vecObj[i]->GetComponent<CRigidBody>();
			
			if (nullptr == pComponent)
				continue;
			
			// ������Ʈ�� Force�� �Ÿ��� ������ �ٲ��ش�.
			float fRatio = Saturate(1.f - fDist / m_Range);
			// Force�� ���� �� * �Ÿ������� �����ְ�
			float Force = m_Force * fRatio;
			
			// �浹�� ������ ������Ʈ�� Force�� �Ÿ� ���� ���ؼ�
			Vec2 vForce = vecObj[i]->GetPos() - GetPos();
			
			// �� �Ÿ��� ���ΰ� �ƴ� ����
			if (!vForce.IsZero())
			{
				// �븻������ ���� ���� ����ŭ �����༭ �ݴ�������� �˹� �ϴ°�ó�� �������ش�.
				vForce.Normalize();
				vForce *= Force;
				pComponent->AddForce(vForce);
			}
		}
		
	}
}