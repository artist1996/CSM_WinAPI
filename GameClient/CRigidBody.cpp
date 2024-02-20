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

		// �ӵ��� �����¸�ŭ ���ش�.
		fSpeed -= m_Friction * DT;

		// ������ ���ؼ� �ӵ��� 0���� ������ ���� ���� ������ �ӵ��� 0���� ����
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
