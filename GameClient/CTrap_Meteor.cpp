#include "pch.h"
#include "CTrap_Meteor.h"

#include "CLevelMgr.h"

#include "CRigidBody.h"
#include "CCollider.h"
#include "CAnimator.h"

#include "CEffect_Meteor.h"

#include "CSpawner_Meteor.h"


CTrap_Meteor::CTrap_Meteor()
	: m_RigidBody(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_HP(0)
	, m_Time(0.f)
{
}

CTrap_Meteor::CTrap_Meteor(Vec2 _Pos, OBJ_ID _ID)
	: m_RigidBody(nullptr)
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_HP(3)
	, m_Time(0.f)
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

	// Spawner
	CSpawner_Meteor* pSpawner = new CSpawner_Meteor(this, GetID());
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DEFAULT, pSpawner);
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

	if (0 >= m_HP)
	{
		Destroy();
		for (int i = 0; i < (int)METEOR_EFFECT::END; ++i)
		{
			CEffect_Meteor* pEffect = new CEffect_Meteor(GetPos(), (METEOR_EFFECT)i);
			SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
		}
	}
}

void CTrap_Meteor::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"PLAYER_ATTACK" == _OtherObj->GetName())
	{
		--m_HP;
	}
}

void CTrap_Meteor::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"PLAYER_JUMPATTACK" == _OtherObj->GetName())
	{
		m_Time += DT;

		if (0.1f <= m_Time)
		{
			--m_HP;
			m_Time = 0.f;
		}
	}
}
