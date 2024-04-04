#include "pch.h"
#include "CTrap_Meteor.h"

#include "CRigidBody.h"
#include "CCollider.h"
#include "CAnimator.h"

CTrap_Meteor::CTrap_Meteor()
	: m_RigidBody(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
}

CTrap_Meteor::CTrap_Meteor(Vec2 _Pos, OBJ_ID _ID)
	: m_RigidBody(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
{
	// Info
	SetName(L"Meteor");
	SetID(_ID);
	SetPos(_Pos);
	SetStartPos(_Pos);
	SetScale(Vec2(120.f, 130.f));

	// Component
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// RigidBody
	if (OBJ_ID::METEOR_LEFT == GetID()
		|| OBJ_ID::METEOR_RIGHT == GetID())
	{
		m_RigidBody->UseGravity(true);
	}
	
	// Collider
	m_Collider->SetScale(GetScale());

	// Animator
	if (OBJ_ID::METEOR_LEFT == GetID())
	{
		m_Animator->LoadAnimation(L"animation\\trap\\meteor\\LEFT.anim");
	}
	
	else if (OBJ_ID::METEOR_RIGHT == GetID())
	{
		m_Animator->LoadAnimation(L"animation\\trap\\meteor\\RIGHT.anim");
	}

	else if (OBJ_ID::METEOR_UP == GetID())
	{
		m_Animator->LoadAnimation(L"animation\\trap\\meteor\\UP.anim");
	}

	else if (OBJ_ID::METEOR_DOWN == GetID())
	{
		m_Animator->LoadAnimation(L"animation\\trap\\meteor\\DOWN.anim");
	}

	else if (OBJ_ID::METEOR_DIAGONAL == GetID())
	{
		m_Animator->LoadAnimation(L"animation\\trap\\meteor\\DIAGONAL.anim");
	}

	// Animation
	if (OBJ_ID::METEOR_LEFT == GetID())
	{
		m_Animator->Play(L"LEFT", true);
	}

	else if (OBJ_ID::METEOR_RIGHT == GetID())
	{
		m_Animator->Play(L"RIGHT", true);
	}

	else if (OBJ_ID::METEOR_UP == GetID())
	{
		m_Animator->Play(L"UP", true);
	}

	else if (OBJ_ID::METEOR_DOWN == GetID())
	{
		m_Animator->Play(L"DOWN", true);
	}

	else if (OBJ_ID::METEOR_DIAGONAL == GetID())
	{
		m_Animator->Play(L"DIAGONAL", false);
	}
}

CTrap_Meteor::~CTrap_Meteor()
{
}

void CTrap_Meteor::tick()
{
	CTrap::tick();

	Vec2 vPos = GetPos();

	if (OBJ_ID::METEOR_RIGHT != GetID() || OBJ_ID::METEOR_LEFT != GetID())
	{
		if(OBJ_ID::METEOR_DOWN == GetID())
		{
			vPos += Vec2(0.f, 1.f) * 700.f * DT;
			SetPos(vPos);
		}

		else if (OBJ_ID::METEOR_UP == GetID())
		{
			vPos += Vec2(0.f, -1.f) * 700.f * DT;
			SetPos(vPos);
		}

		if (GetStartPos().GetDistance(vPos) > 1000.f)
		{
			SetPos(GetStartPos());
		}	
	}

	else
	{

	}
}