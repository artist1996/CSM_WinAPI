#include "pch.h"
#include "CRigidBody.h"

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_Friction(200.f)
	, m_MaxWalkSpeed(0.f)
	, m_InitWalkSpeed(0.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finaltick()
{
	// F = M x A
	Vec2 vObjPos = GetOwner()->GetPos();
	
	Vec2 vAccel = m_Force / m_Mass;
		

	m_Velocity += vAccel * DT;
	
	// 최대 속도 설정
	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxWalkSpeed;
	}

	// 최소 속도 보정
	if (0.f != m_InitWalkSpeed && m_Velocity.Length() < 10.f && !vAccel.IsZero())
	{
		Vec2 vForceDir = m_Force;
		vForceDir.Normalize();
		m_Velocity = vForceDir * m_InitWalkSpeed;
	}

	// 가해지는 힘이 0일 때
	if (m_Force.IsZero())
	{
		// 점점 줄어들다가 0보다 밑으로 내려가면 0으로 보정
		float fSpeed = m_Velocity.Length();

		// 속도를 마찰력만큼 빼준다.
		fSpeed -= m_Friction * DT;

		// 마찰에 의해서 속도가 0보다 낮아질 수는 없기 때문에 속도를 0으로 고정
		if (fSpeed < 0.f)
		{
			fSpeed = 0.f;
		}

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= fSpeed;
	}

	vObjPos += m_Velocity * DT;

	GetOwner()->SetPos(vObjPos);
	
	m_Force = Vec2(0.f, 0.f);
}
