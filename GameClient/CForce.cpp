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
	// 시간 누적
	m_Age += DT;
	DrawDebugCircle(PEN_TYPE::PEN_BLUE, GetPos(), Vec2(m_Range * 2.f, m_Range * 2.f), 0.f);
	
	if (m_Time < m_Age)
	{
		Destroy();
	}
}

void CForce::AddForce(LAYER_TYPE _Type)
{
	// 현재 레벨을 들고와서 해당 타입의 Object들을 다 가져온다.
	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	const vector<CObj*>& vecObj = pLevel->GetObjects(_Type);
	
	
	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		// Force의 힘의 거리가 Force와 Object의 거리보다 크다면 충돌 한거다.
		float fDist = GetPos().GetDistance(vecObj[i]->GetPos());

		if (fDist <= m_Range)
		{
			// rigidbody 컴포넌트 들고온다.
			CRigidBody* pComponent = vecObj[i]->GetComponent<CRigidBody>();
			
			if (nullptr == pComponent)
				continue;
			
			// 오브젝트와 Force의 거리를 비율로 바꿔준다.
			float fRatio = Saturate(1.f - fDist / m_Range);
			// Force에 기존 힘 * 거리비율을 곱해주고
			float Force = m_Force * fRatio;
			
			// 충돌한 순간에 오브젝트와 Force의 거리 값을 구해서
			Vec2 vForce = vecObj[i]->GetPos() - GetPos();
			
			// 이 거리가 제로가 아닐 때에
			if (!vForce.IsZero())
			{
				// 노말라이즈 해준 다음 힘만큼 곱해줘서 반대방향으로 넉백 하는거처럼 설계해준다.
				vForce.Normalize();
				vForce *= Force;
				pComponent->AddForce(vForce);
			}
		}
		
	}
}