#include "pch.h"
#include "CEffect_Wall.h"

#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CEffect_Wall::CEffect_Wall(CObj* _Owner, CRigidBody* _RigidBody)
	: m_Owner(_Owner)
	, m_RigidBody(_RigidBody)
	, m_Animator(nullptr)
{
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		SetPos(Vec2(m_Owner->GetPos().x + 40.f, m_Owner->GetPos().y));
		m_Animator->LoadAnimation(L"animation\\player\\effect\\right\\EFFECT_WALL_RIGHT.anim");
		m_Animator->Play(L"EFFECT_WALL_RIGHT", true);
	}

	else if (DIRECTION::LEFT == m_Owner->GetDirection())
	{
		SetPos(Vec2(m_Owner->GetPos().x - 40.f, m_Owner->GetPos().y));
		m_Animator->LoadAnimation(L"animation\\player\\effect\\left\\EFFECT_WALL_LEFT.anim");
		m_Animator->Play(L"EFFECT_WALL_LEFT", true);
	}
}

CEffect_Wall::~CEffect_Wall()
{
}


void CEffect_Wall::tick()
{
	CObj::tick();
	if (!m_RigidBody->IsWall())
		Destroy();

	if (DIRECTION::RIGHT == m_Owner->GetDirection())
	{
		SetPos(Vec2(m_Owner->GetPos().x + 40.f, m_Owner->GetPos().y));
	}

	else if (DIRECTION::LEFT == m_Owner->GetDirection())
	{
		SetPos(Vec2(m_Owner->GetPos().x - 40.f, m_Owner->GetPos().y));
	}
}