#include "pch.h"
#include "CMonster_Mettool.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CFSM.h"
#include "CPlayer.h"
#include "CMettool_Idle.h"
#include "CMettool_Patrol.h"
#include "CMettool_Attack.h"

CMonster_Mettool::CMonster_Mettool(Vec2 _Pos, Vec2 _Scale, int _HP, float _DetectRange)
	: m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
	, m_MaxDistance(100.f)
{
	// Info
	SetName(L"Mettool");
	SetPos(_Pos);
	SetScale(_Scale);
	SetHP(_HP);
	SetDetectRange(_DetectRange);
	SetSpeed(100.f);
	m_vCenterPos = _Pos;
	SetDirection(DIRECTION::LEFT);
	SetID(OBJ_ID::METTOOL);
	
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -25.f));
	m_Collider->SetScale(GetScale());

	// Animator
	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\left\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\left\\PATROL_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\left\\ATTACK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\left\\JUMP_LEFT.anim");

	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\right\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\right\\PATROL_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\mettool\\right\\ATTACK_RIGHT.anim");


	// RigidBody
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(50.f);
	
	// FSM
	m_FSM->AddState(L"IDLE", new CMettool_Idle);
	m_FSM->AddState(L"PATROL", new CMettool_Patrol);
	m_FSM->AddState(L"ATTACK", new CMettool_Attack);
}

CMonster_Mettool::~CMonster_Mettool()
{
}

void CMonster_Mettool::begin()
{
	CMonster::begin();
	
	CObj * pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");
	float DetectRange = GetDetectRange();
	float Speed = GetSpeed();
	m_FSM->SetBlackboardData(L"DetectRange", DATA_TYPE::FLOAT, &DetectRange);
	m_FSM->SetBlackboardData(L"MaxDistance", DATA_TYPE::FLOAT, &m_MaxDistance);
	m_FSM->SetBlackboardData(L"Speed", DATA_TYPE::FLOAT, &Speed);
	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pPlayer);
	m_FSM->SetBlackboardData(L"CenterPos", DATA_TYPE::VEC2, &m_vCenterPos);

	m_FSM->ChangeState(L"IDLE");
}


void CMonster_Mettool::Shoot()
{
	
}