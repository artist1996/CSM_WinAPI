#include "pch.h"
#include "CRigidBody.h"

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_Friction(500.f)
	, m_MaxWalkSpeed(0.f)
	, m_InitWalkSpeed(0.f)
	, m_MaxGravitySpeed(0.f)
	, m_JumpSpeed(400.f)
	, m_GravityAccel(980.f)
	, m_Ground(false)
	, m_Wall(false)
	, m_UseGravity(false)
	, m_PrevWall(false)
{
}

CRigidBody::CRigidBody(const CRigidBody& _Other)
	: CComponent(_Other)
	, m_Mass(_Other.m_Mass)
	, m_InitWalkSpeed(_Other.m_InitWalkSpeed)
	, m_MaxWalkSpeed(_Other.m_MaxWalkSpeed)
	, m_MaxGravitySpeed(_Other.m_MaxGravitySpeed)
	, m_Friction(_Other.m_Friction)
	, m_GravityAccel(_Other.m_GravityAccel)
	, m_UseGravity(_Other.m_UseGravity)
	, m_Ground(_Other.m_Ground)
	, m_JumpSpeed(_Other.m_JumpSpeed)
	, m_GroundFunc(nullptr)
	, m_AirFunc(nullptr)
	, m_GroundInst(nullptr)
	, m_GroundDelegate(nullptr)
	, m_AirInst(nullptr)
	, m_AirDelegate(nullptr)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	m_VelocityByGravity += Vec2(0.f, -1.f) * m_JumpSpeed;
	SetGround(false);
	SetJump(true);
}

void CRigidBody::finaltick()
{
	m_PrevWall = m_Wall;
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
	if (m_UseGravity && !m_Ground)
	{
		m_VelocityByGravity += Vec2(0.f, 1.f) * m_GravityAccel * DT;

		if (0.f != m_MaxGravitySpeed && m_MaxGravitySpeed < m_VelocityByGravity.Length())
		{
			m_VelocityByGravity.Normalize();
			m_VelocityByGravity *= m_MaxGravitySpeed;
		}
	}

	if (m_UseGravity && m_Ground)
	{
		m_VelocityByGravity = Vec2(0.f, 0.f);
	}

	if (m_UseGravity && m_Wall)
	{
		m_VelocityByGravity = Vec2(0.f, 50.f);
	}

	if (m_UseGravity && m_Block)
	{
		m_VelocityByGravity = Vec2(0.f, 0.f);
	}
	
	Vec2 vFinalVelocity = m_Velocity + m_VelocityByGravity;

	vObjPos += vFinalVelocity * DT;

	GetOwner()->SetPos(vObjPos);
	
	m_Force = Vec2(0.f, 0.f);
	m_AddVelocity = Vec2(0.f, 0.f);
}