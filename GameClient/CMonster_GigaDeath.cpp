#include "pch.h"
#include "CMonster_GigaDeath.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CFSM.h"

#include "CGigaDeath_Idle.h"
#include "CGigaDeath_Attack.h"

CMonster_GigaDeath::CMonster_GigaDeath()
	: m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
{
}

CMonster_GigaDeath::CMonster_GigaDeath(Vec2 _Pos, Vec2 _Scale, int _HP, float _DetectRange)
	: m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
{
	//Info
	SetName(L"GigaDeath");
	SetPos(_Pos);
	SetScale(_Scale);
	SetHP(_HP);
	SetDetectRange(_DetectRange);
	SetDirection(DIRECTION::LEFT);
	SetID(OBJ_ID::GIGADEATH);
	
	// Component
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// RigidBody
	m_RigidBody->UseGravity(true);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -100.f));
	m_Collider->SetScale(_Scale);

	// Animation
	m_Animator->LoadAnimation(L"animation\\monster\\gigadeath\\IDLE.anim");

	m_Animator->Play(L"IDLE", false);
	// FSM
	m_FSM->AddState(L"IDLE", new CGigaDeath_Idle);
	m_FSM->AddState(L"ATTACK", new CGigaDeath_Attack);
}

CMonster_GigaDeath::~CMonster_GigaDeath()
{
}

void CMonster_GigaDeath::begin()
{
	CObj* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");

	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pTarget);
	m_FSM->ChangeState(L"IDLE");
}

void CMonster_GigaDeath::tick()
{
	CObj::tick();
}