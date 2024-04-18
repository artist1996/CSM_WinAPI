#include "pch.h"
#include "CMonster_Raiden.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CFSM.h"
#include "CAnimation.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CRaiden_Idle.h"
#include "CRaiden_StandBy.h"
#include "CRaiden_Attack.h"


CMonster_Raiden::CMonster_Raiden()
	: m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_FSM(nullptr)
{
}

CMonster_Raiden::CMonster_Raiden(Vec2 _Pos, Vec2 _Scale, int _HP, float _DetectRange)
	: m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_FSM(nullptr)
{
	// Info
	SetName(L"Raiden");
	SetPos(_Pos);
	SetScale(_Scale);
	SetHP(_HP);
	SetDetectRange(_DetectRange);
	SetDirection(DIRECTION::LEFT);
	SetID(OBJ_ID::RAIDEN);

	// Component
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// RigidBody
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(50.f);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -90.f));
	m_Collider->SetScale(_Scale);

	// Animator
	m_Animator->LoadAnimation(L"animation\\monster\\raiden\\IDLE.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\raiden\\ATTACK.anim");

	// FSM
	m_FSM->AddState(L"IDLE", new CRaiden_Idle);
	m_FSM->AddState(L"ATTACK", new CRaiden_Attack);
	m_FSM->AddState(L"STANDBY", new CRaiden_StandBy);

}

CMonster_Raiden::~CMonster_Raiden()
{
}

void CMonster_Raiden::begin()
{
	CMonster::begin();

	CObj* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");
	float Range = GetDetectRange();
	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pTarget);
	m_FSM->SetBlackboardData(L"DetectRange", DATA_TYPE::FLOAT, &Range);

	m_FSM->ChangeState(L"IDLE");

}
