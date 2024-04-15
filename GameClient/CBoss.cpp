#include "pch.h"
#include "CBoss.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CFSM.h"

#include "CBoss_Enter.h"
#include "CBoss_Idle.h"
#include "CBoss_Hadouken.h"
#include "CBoss_Soryugen.h"
#include "CBoss_DiveKick.h"
#include "CBoss_Breath.h"
#include "CBoss_Destroy.h"
#include "CBoss_Dead.h"

CBoss::CBoss()
	: m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
	, m_TargetPlatform(nullptr)
	, m_HP(0)
{
}

CBoss::CBoss(Vec2 _Pos, int _HP)
	: m_Collider(nullptr)
	, m_RigidBody(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
	, m_TargetPlatform(nullptr)
	, m_HP(_HP)
	, m_CenterPos(_Pos)
	, m_Time(0.f)
{
	// Info
	SetName(L"Dragoon");
	SetPos(_Pos);
	SetDirection(DIRECTION::LEFT);
	SetHp(_HP);
	
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -70.f));
	m_Collider->SetScale(Vec2(80.f, 140.f));

	// RigidBody
	//m_RigidBody->UseGravity(false);
	m_RigidBody->SetJumpSpeed(700.f);
	
	// Animator
	m_Animator->LoadAnimation(L"animation\\boss\\ENTER.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\START.anim");
	
	//LEFT
	m_Animator->LoadAnimation(L"animation\\boss\\left\\HADOUKEN_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\DIVEKICK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\SORYUGEN_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\DESTROY_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\DEAD_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\LANDING_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\BREATH_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\left\\FALL_LEFT.anim");


	//RIGHT
	m_Animator->LoadAnimation(L"animation\\boss\\right\\BREATH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\DEAD_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\DESTROY_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\DIVEKICK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\HADOUKEN_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\LANDING_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\SORYUGEN_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\right\\FALL_RIGHT.anim");

	CTexture* pTex = CAssetMgr::GetInst()->LoadTexture(L"HIT_LEFT", L"texture\\MagmaDragoon_HITLEFT.png");
	pTex = CAssetMgr::GetInst()->LoadTexture(L"HIT_RIGHT", L"texture\\MagmaDragoon_HITRIGHT.png");

	// FSM
	m_FSM->AddState(L"ENTER", new CBoss_Enter);
	m_FSM->AddState(L"IDLE", new CBoss_Idle);
	m_FSM->AddState(L"HADOUKEN", new CBoss_Hadouken);
	m_FSM->AddState(L"SORYUGEN", new CBoss_Soryugen);
	m_FSM->AddState(L"DIVEKICK", new CBoss_DiveKick);
	m_FSM->AddState(L"BREATH", new CBoss_Breath);
	m_FSM->AddState(L"DESTROY", new CBoss_Destroy);
	m_FSM->AddState(L"DEAD", new CBoss_Dead);
}

CBoss::~CBoss()
{
}

void CBoss::begin()
{
	CObj* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");
	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pTarget);
	m_FSM->SetBlackboardData(L"CenterPos", DATA_TYPE::VEC2, &m_CenterPos);
	m_FSM->SetBlackboardData(L"TargetPlatform",DATA_TYPE::OBJECT, m_TargetPlatform);
}

void CBoss::tick()
{
	CObj::tick();

	if (IsHit())
	{
		m_Time += DT;
	}

	if (0.1f <= m_Time)
	{
		SetHit(false);
		m_Time = 0.f;
	}
}

void CBoss::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (!IsHit() && LAYER_TYPE::PLAYER_ATTACK == _OtherObj->GetLayerType())
	{
		--m_HP;
		MinusHp();
		SetHit(true);
	}

	if (0 >= m_HP)
	{
		m_FSM->ChangeState(L"DESTROY");
	}
}
