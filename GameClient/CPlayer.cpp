#include "pch.h"
#include "CPlayer.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CDbgRender.h"
#include "CRigidBody.h"

#include "CMissile.h"
#include "CGuidedMissile.h"
#include "CCamera.h"

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
{
	// Player 의 컴포넌트 설정
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, -48.f));
	m_BodyCol->SetScale(Vec2(100.f, 100.f));
	m_BodyCol->SetActive(true);

	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", L"texture\\link_32.bmp");
	m_Animator->CreateAnimation(L"IDLE_DOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.f), 3, 10);
	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.f), 3, 10);
	m_Animator->CreateAnimation(L"IDLE_UP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.f), 1, 1);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), 3, 10);

	m_Animator->CreateAnimation(L"WALK_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 18);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.f), 10, 18);
	m_Animator->CreateAnimation(L"WALK_UP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.f), 10, 18);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.f), 10, 18);

	m_Animator->FindAnimation(L"WALK_DOWN")->Save(L"animation\\player\\");

	m_Animator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");

	m_Animator->Play(L"IDLE_RIGHT", true);

	//CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", L"texture\\link_32.bmp");
	//m_Animator->CreateAnimation(L"WALK_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 18);
	//m_Animator->FindAnimation(L"WALK_DOWN")->Save(L"animation\\player\\");
	//
	//m_Animator->Play(L"WALK_DOWN", true);
	//m_Animator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");
	//m_Animator->Play(L"WALK_DOWN", true);

	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxWalkSpeed(300.f);
	m_RigidBody->SetInitWalkSpeed(200.f);
	m_RigidBody->SetFriction(2000.f);

	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(1500.f);
	m_RigidBody->SetJumpSpeed(600.f);


	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);


	// 카메라
	CCamera::GetInst()->SetOwner(this);
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, m_Speed(_Other.m_Speed)
	, m_PlayerImg(_Other.m_PlayerImg)
	, m_BodyCol(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
{
	m_BodyCol = GetComponent<CCollider>();
	m_Animator = GetComponent<CAnimator>();
	m_RigidBody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
}

void CPlayer::begin()
{
}

void CPlayer::tick()
{	
	CObj::tick();
	Vec2 vPos = GetPos();

	// 왼쪽키가 눌린적이 있으면(눌려있으면) 왼쪽으로 1픽셀 이동	
	if (KEY_PRESSED(KEY::LEFT) && !m_RigidBody->IsWall())
	{
		//m_RigidBody->AddForce(Vec2(-1000.f, 0.f));
		//vPos += Vec2(-300.f, 0.f) * DT;
		vPos += Vec2(-300.f, 0.f) * DT;
	}
	else if (KEY_TAP(KEY::LEFT))
	{
		//m_Animator->Play(L"WALK_LEFT", true);
	}
	else if (KEY_RELEASED(KEY::LEFT))
	{
		//m_Animator->Play(L"IDLE_LEFT", true);
	}
	else if (KEY_TAP(KEY::X) && m_RigidBody->IsWall())
	{
		vPos += Vec2(-50.f, 0.f) * DT;
		Jump();
	}

	else if (KEY_PRESSED(KEY::LEFT) && m_RigidBody->IsWall())
	{
		vPos += Vec2(-0.1f, 0.f) * DT;
	}

	if (KEY_PRESSED(KEY::RIGHT) && !m_RigidBody->IsWall())
	{
		//m_RigidBody->AddForce(Vec2(1000.f, 0.f));
		vPos += Vec2(300.f, 0.f) * DT;
	}
	else if (KEY_TAP(KEY::RIGHT))
	{
		//m_Animator->Play(L"WALK_RIGHT", true);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		//m_Animator->Play(L"IDLE_RIGHT", true);
	}

	else if (KEY_PRESSED(KEY::RIGHT) && KEY_TAP(KEY::X) && m_RigidBody->IsWall())
	{ 
		vPos += Vec2(50.f, 0.f) * DT;
		Jump();
	}

	if (KEY_PRESSED(KEY::UP))
	{
		//m_RigidBody->AddForce(Vec2(0.f, -1000.f));
	}
	else if (KEY_TAP(KEY::UP))
	{
		//m_Animator->Play(L"WALK_UP", true);
	}
	else if (KEY_RELEASED(KEY::UP))
	{
		//m_Animator->Play(L"IDLE_UP", true);
	}


	
	if (KEY_PRESSED(KEY::DOWN))
	{
		//m_RigidBody->AddForce(Vec2(0.f, 1000.f));
	}
	else if (KEY_TAP(KEY::DOWN))
	{
		//m_Animator->Play(L"WALK_DOWN", true);
	}
	else if (KEY_RELEASED(KEY::DOWN))
	{
		//m_Animator->Play(L"IDLE_DOWN", true);
	}

	// Space 키가 눌리면 점프한다.
	if (KEY_TAP(KEY::X))
	{
		Jump();
	}

	SetPos(vPos);
}


void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	int a = 0;
}

void CPlayer::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	int a = 0;
}

void CPlayer::Jump()
{
	m_RigidBody->Jump();
}

void CPlayer::Shoot()
{
	CMissile * pMissile = new CGuidedMissile;
	pMissile->SetName(L"Missile");
	
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;
	
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));
	
	SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);
	
	LOG(LOG_TYPE::DBG_WARNING, L"미사일 발사");
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