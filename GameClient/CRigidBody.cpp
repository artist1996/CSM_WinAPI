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

	// �ִ� �ӵ� ����
	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxWalkSpeed;
	}

	// �ּ� �ӵ� ����
	if (0.f != m_InitWalkSpeed && m_Velocity.Length() < 10.f && !vAccel.IsZero())
	{
		Vec2 vForceDir = m_Force;
		vForceDir.Normalize();
		m_Velocity = vForceDir * m_InitWalkSpeed;
	}

	// �������� ���� 0�� ��
	if (m_Force.IsZero())
	{
		// ���� �پ��ٰ� 0���� ������ �������� 0���� ����
		float fSpeed = m_Velocity.Length();

		if (m_UseGravity && !m_Ground)
		{
			fSpeed -= m_Friction * DT * 0.2f;
		}
		// �ӵ��� �����¸�ŭ ���ش�.
		else
		{
			fSpeed -= m_Friction * DT;
		}

		// ������ ���ؼ� �ӵ��� 0���� ������ ���� ���� ������ �ӵ��� 0���� ����
		if (fSpeed < 0.f)
		{
			fSpeed = 0.f;
		}

		if (!m_Velocity.IsZero())
			m_Velocity.Normalize();

		m_Velocity *= fSpeed;
	}

	// �߷� ���ӵ��� ���� �ӵ� ����
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