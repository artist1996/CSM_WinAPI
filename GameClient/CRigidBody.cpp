#include "pch.h"
#include "CRigidBody.h"

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_Friction(500.f)
	, m_MaxWalkSpeed(0.f)
	, m_InitWalkSpeed(0.f)
	, m_Ground(false)
	, m_Climb(false)
	, m_Air(false)
	, m_GravityAccel(980.f)
	, m_UseGravity(false)
	, m_JumpSpeed(400.f)
	, m_MaxGravitySpeed(0.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	if (m_Ground && m_Climb)
	{
		m_VelocityByGravity += Vec2(0.f, -0.1f) * m_JumpSpeed;
		SetGround(false);
		SetClimb(false);
	}

	else if (m_Ground && !m_Climb)
	{
		m_VelocityByGravity += Vec2(0.f, -1.f) * m_JumpSpeed;
		SetGround(false);
	}

	else if (!m_Ground && m_Climb)
	{
		m_VelocityByGravity += Vec2(0.f, -1.f) * m_JumpSpeed;
		SetClimb(false);
	}
}

void CRigidBody::finaltick()
{
	// F = M x A
	Vec2 vObjPos = GetOwner()->GetPos();
	
	Vec2 vAccel = m_Force / m_Mass;
		
	if (m_UseGravity && !m_Ground)
	{
		m_Velocity += vAccel * DT;
	}

	else
	{
		m_Velocity += vAccel * DT * 1.f;
	}

	// 최대 속도 제한
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

		if (m_UseGravity && !m_Ground)
		{
			fSpeed -= m_Friction * DT * 0.2f;
		}
		// 속도를 마찰력만큼 빼준다.
		else
		{
			fSpeed -= m_Friction * DT;
		}

		// 마찰에 의해서 속도가 0보다 낮아질 수는 없기 때문에 속도를 0으로 고정
		if (fSpeed < 0.f)
		{
			fSpeed = 0.f;
		}

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= fSpeed;
	}

	// 중력 가속도에 의한 속도 증가
	if (m_UseGravity && !m_Ground && !m_Climb)
	{
		m_VelocityByGravity += Vec2(0.f, 1.f) * m_GravityAccel * DT;

		if (0.f != m_MaxGravitySpeed && m_MaxGravitySpeed < m_VelocityByGravity.Length())
		{
			m_VelocityByGravity.Normalize();
			m_VelocityByGravity *= m_MaxGravitySpeed;
		}
	}

	else if (m_UseGravity && !m_Ground && m_Climb)
	{
		m_VelocityByGravity += Vec2(0.f, 0.1f) * m_GravityAccel * DT;

		if (m_VelocityByGravity.Length() > 20.f)
		{
			m_VelocityByGravity.Normalize();
			m_VelocityByGravity += Vec2(0.f, 0.1f) * m_GravityAccel * DT;
		}
	}

	

	Vec2 vFinalVelocity = m_Velocity + m_VelocityByGravity;

	vObjPos += vFinalVelocity * DT;

	GetOwner()->SetPos(vObjPos);
	
	m_Force = Vec2(0.f, 0.f);
	m_AddVelocity = Vec2(0.f, 0.f);
	
}