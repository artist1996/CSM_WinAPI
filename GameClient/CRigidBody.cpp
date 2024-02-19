#include "pch.h"
#include "CRigidBody.h"

CRigidBody::CRigidBody()
	: m_Mass(1.f)
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
	
	if (0.f != m_MaxWalkSpeed && m_MaxWalkSpeed < m_Velocity.Length())
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxWalkSpeed;
	}

	//m_Velocity.Normalize();

	vObjPos += m_Velocity * DT;

	GetOwner()->SetPos(vObjPos);
	
	m_Force = Vec2(0.f, 0.f);
}
