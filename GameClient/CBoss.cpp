#include "pch.h"
#include "CBoss.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CFSM.h"

CBoss::CBoss()
	: m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
	, m_Target(nullptr)
	, m_HP(0)
{
}

CBoss::CBoss(Vec2 _Pos, int _HP)
	: m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
	, m_Target(nullptr)
	, m_HP(_HP)
{
	// Info
	SetName(L"Dragoon");
	SetPos(_Pos);
	SetDirection(DIRECTION::LEFT);
	
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetScale(Vec2(100.f, 100.f));

	// RigidBody
	m_RigidBody->UseGravity(true);
	
	// Animator
	m_Animator->LoadAnimation(L"animation\\boss\\ENTER.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\STNADBY.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\HADOUKEN.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\DIVEKICK.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\SORYUGEN.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\DESTROY.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\DEAD.anim");

	// FSM
	//m_FSM->AddState(L"ENTER", new CBoss_Enter);
	//m_FSM->AddState(L"STANDBY", new CBoss_StandBy);
	//m_FSM->AddState(L"HADOUKEN", new CBoss_Hadouken);
	//m_FSM->AddState(L"DIVEKICK", new CBoss_Soryugen);
	//m_FSM->AddState(L"DESTROY", new CBoss_Destroy);
	//m_FSM->AddState(L"DEAD", new CBoss_Dead);
}

CBoss::~CBoss()
{
}
