#include "pch.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CDbgRender.h"
#include "CRigidBody.h"
#include "CFSM.h"

#include "CMissile.h"
#include "CPlayer_Attack.h"
#include "CPlayer_JumpAttack.h"
#include "CCamera.h"

#include "CState_Player.h"
#include "CState_Start.h"
#include "CState_Enter.h"
#include "CState_Idle.h"
#include "CState_Move.h"
#include "CState_Dash.h"
#include "CState_Attack01.h"
#include "CState_Attack02.h"
#include "CState_Attack03.h"
#include "CState_Jump.h"
#include "CState_Fall.h"
#include "CState_Fastfall.h"
#include "CState_Landing.h"
#include "CState_Rakuouha.h"
#include "CState_WallEnter.h"
#include "CState_WallIdle.h"
#include "CState_Block.h"
#include "CState_WallKick.h"
#include "CState_Hit.h"
#include "CState_Victory.h"
#include "CState_Dead.h"

void BeGround()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Grounded");
}

void BeAir()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Air");
}


CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
	, m_eState(PLAYER_STATE::IDLE)
	, m_Invincible(false)
	, m_InvincibleTime(0.f)
	, m_HitBox(nullptr)
	, m_AlwaysInvincible(false)
	, m_BlackZero(false)
{
	SetHp(15);
	// Player 의 컴포넌트 설정
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_HitBox = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, -50.f));
	m_BodyCol->SetScale(Vec2(100.f,90.f));
	m_BodyCol->SetActive(true);

	m_HitBox->SetName(L"HitBox");
	m_HitBox->SetOffsetPos(Vec2(0.f, -50.f));
	m_HitBox->SetScale(Vec2(40.f, 40.f));
	m_HitBox->SetActive(true);
	
	//Right Animation
	m_Animator->LoadAnimation(L"animation\\player\\right\\WALK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\DASH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\ATTACK01_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\ATTACK02_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\ATTACK03_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\ENTER.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\FASTFALL_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\HURT_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\FALL_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\RAKUOUHA_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\START.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\WALL_ENTER_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\WALL_IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\WALL_ATTACK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\WALLKICK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\HIT_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\LANDING_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\VICTORY_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\DEAD_RIGHT.anim");


	// Left Animation
	m_Animator->LoadAnimation(L"animation\\player\\left\\WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\DASH_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\ATTACK01_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\ATTACK02_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\ATTACK03_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\FASTFALL_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\HURT_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\FALL_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\RAKUOUHA_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\WALL_ENTER_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\WALL_IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\WALL_ATTACK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\WALLKICK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\HIT_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\LANDING_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\left\\VICTORY_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\right\\DEAD_LEFT.anim");


	// Black Zero Right
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_ATTACK01_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_ATTACK02_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_ATTACK03_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_VICTORY_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_WALLIDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_DASH_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_FALL_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_FASTFALL_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_IDLE_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_JUMP_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_LANDING_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_WALK_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_WALLENTER_RIGHT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\right\\BLACK_WALLKICK_RIGHT.anim");

	// Black Zero Left
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_ATTACK01_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_ATTACK02_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_ATTACK03_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_VICTORY_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_WALLIDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_DASH_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_FALL_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_FASTFALL_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_IDLE_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_JUMP_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_LANDING_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_WALK_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_WALLENTER_LEFT.anim");
	m_Animator->LoadAnimation(L"animation\\player\\blackzero\\left\\BLACK_WALLKICK_LEFT.anim");


	// Rigidbody
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxWalkSpeed(300.f);
	m_RigidBody->SetInitWalkSpeed(200.f);
	m_RigidBody->SetFriction(2000.f);

	m_RigidBody->UseGravity(false);
	m_RigidBody->SetMaxGravitySpeed(2000.f);
	m_RigidBody->SetJumpSpeed(600.f);
	
	// FSM
	m_FSM->AddState(L"START", new CState_Start);
	m_FSM->AddState(L"ENTER", new CState_Enter);
	m_FSM->AddState(L"IDLE", new CState_Idle);
	m_FSM->AddState(L"MOVE", new CState_Move);
	m_FSM->AddState(L"DASH", new CState_Dash);
	m_FSM->AddState(L"ATTACK01", new CState_Attack01);
	m_FSM->AddState(L"ATTACK02", new CState_Attack02);
	m_FSM->AddState(L"ATTACK03", new CState_Attack03);
	m_FSM->AddState(L"JUMP", new CState_Jump);
	m_FSM->AddState(L"FALL", new CState_Fall);
	m_FSM->AddState(L"FASTFALL", new CState_Fastfall);
	m_FSM->AddState(L"LANDING", new CState_Landing);
	m_FSM->AddState(L"RAKUOUHA", new CState_Rakuouha);
	m_FSM->AddState(L"WALL_ENTER", new CState_WallEnter);
	m_FSM->AddState(L"WALL_IDLE", new CState_WallIdle);
	m_FSM->AddState(L"BLOCK", new CState_Block);
	m_FSM->AddState(L"WALLKICK", new CState_WallKick);
	m_FSM->AddState(L"HIT", new CState_Hit);
	m_FSM->AddState(L"VICTORY", new CState_Victory);
	m_FSM->AddState(L"DEAD", new CState_Dead);

	//m_FSM->ChangeState(L"START");
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Speed(_Other.m_Speed)
	, m_PlayerImg(_Other.m_PlayerImg)
	, m_BodyCol(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_FSM(nullptr)
	, m_Invincible(false)
	, m_InvincibleTime(0.f)
	, m_eState(PLAYER_STATE::END)
	, m_HitBox(nullptr)
	, m_BlackZero(false)
{
	m_BodyCol = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
}

void CPlayer::CreateAttack(ATTACK_TYPE _Type)
{
	CPlayer_Attack* pAttack = new CPlayer_Attack(this, GetPos(), _Type);
	pAttack->SetAnimator(m_Animator);
	pAttack->SetOwner(this);
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_ATTACK, pAttack);
}

void CPlayer::CreateJumpAttack()
{
	CPlayer_JumpAttack* pJumpAttack = new CPlayer_JumpAttack(this, m_Animator, GetPos());
	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(LAYER_TYPE::PLAYER_ATTACK, pJumpAttack);
}

void CPlayer::begin()
{
	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);
}

void CPlayer::tick()
{	
	CObj::tick();
	Vec2 vPos = GetPos();

	static float logtime = 0.f;

	logtime += DT;

	if (1.f <= logtime)
	{
		wchar_t szBuff[256] = {};
		swprintf_s(szBuff, L"%f, %f", vPos.x, vPos.y);
		LOG(LOG_TYPE::DBG_ERROR, szBuff);
		logtime = 0.f;
	}

	if (m_Invincible)
	{
		m_InvincibleTime += DT;
	}

	if (3.f <= m_InvincibleTime)
	{
		m_Invincible = false;
		m_InvincibleTime = 0.f;
	}

	if (KEY_TAP(KEY::O))
	{
		m_AlwaysInvincible = true;
		m_BlackZero = true;

		if (DIRECTION::RIGHT == GetDirection())
		{
			m_Animator->Play(L"BLACK_IDLE_RIGHT", true);
		}

		else if (DIRECTION::LEFT == GetDirection())
		{
			m_Animator->Play(L"BLACK_IDLE_LEFT", true);
		}
	}

	else if (KEY_TAP(KEY::I))
	{
		m_AlwaysInvincible = false;
	}

	SetPos(vPos);
}

void CPlayer::render()
{
	CObj::render();
}

void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"HitBox" == _OwnCollider->GetName() && !m_AlwaysInvincible)
	{
		if (LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
			|| LAYER_TYPE::MONSTER == _OtherObj->GetLayerType()
			|| LAYER_TYPE::TRAP == _OtherObj->GetLayerType()
			|| LAYER_TYPE::MONSTER_MISSILE == _OtherObj->GetLayerType()
			|| LAYER_TYPE::BOSS_ATTACK == _OtherObj->GetLayerType())
		{
			if (!m_Invincible)
			{
				m_Invincible = true;
				m_FSM->ChangeState(L"HIT");
				MinusHp();
			}
		}
	}
}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlayer::Jump()
{
	m_RigidBody->Jump();
}

// Animation 추가
	//CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", L"texture\\link_32.bmp");
	//m_Animator->CreateAnimation(L"IDLE_DOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.f), 3, 10);
	//m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.f), 3, 10);
	//m_Animator->CreateAnimation(L"IDLE_UP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.f), 1, 1);
	//m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), 3, 10);
	//
	//m_Animator->CreateAnimation(L"WALK_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 18);
	//m_Animator->CreateAnimation(L"WALK_LEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.f), 10, 18);
	//m_Animator->CreateAnimation(L"WALK_UP",	  pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.f), 10, 18);	
	//m_Animator->CreateAnimation(L"WALK_RIGHT",pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.f), 10, 18);

	//m_Animator->FindAnimation(L"WALK_DOWN")->Save(L"animation\\player\\");

	//m_Animator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");

	//m_Animator->Play(L"IDLE_DOWN", true);