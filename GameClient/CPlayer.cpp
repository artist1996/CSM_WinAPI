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




CPlayer::CPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
{
	// Player �� ������Ʈ ����
	m_HeadCol = (CCollider*)AddComponent(new CCollider);
	m_BodyCol = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);

	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0.f, -40.f));
	m_HeadCol->SetScale(Vec2(30.f, 30.f));
	m_HeadCol->SetActive(true);
	
	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 20.f));
	m_BodyCol->SetScale(Vec2(30.f, 60.f));
	m_BodyCol->SetActive(true);

	//CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", L"texture\\link_32.bmp");
	//m_Animator->CreateAnimation(L"WALK_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 18);
	//m_Animator->FindAnimation(L"WALK_DOWN")->Save(L"animation\\player\\");
	//
	//m_Animator->Play(L"WALK_DOWN", true);
	m_Animator->LoadAnimation(L"animation\\player\\WALK_DOWN.anim");
	m_Animator->Play(L"WALK_DOWN", true);

	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxWalkSpeed(300.f);
	m_RigidBody->SetInitWalkSpeed(200.f);
	m_RigidBody->SetFriction(2000.f);
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::begin()
{
}

void CPlayer::tick()
{	
	Vec2 vPos = GetPos();

	// ����Ű�� �������� ������(����������) �������� 1�ȼ� �̵�	
	if (KEY_PRESSED(KEY::LEFT))
	{
		m_RigidBody->AddForce(Vec2(-1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::LEFT))
	{
		//m_Animator->Play(L"WALK_LEFT", true);
	}
	else if (KEY_RELEASED(KEY::LEFT))
	{
		//m_Animator->Play(L"IDLE_LEFT", true);
	}


	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_RigidBody->AddForce(Vec2(1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::RIGHT))
	{
		//m_Animator->Play(L"WALK_RIGHT", true);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		//m_Animator->Play(L"IDLE_RIGHT", true);
	}

	if (KEY_PRESSED(KEY::UP))
	{
		m_RigidBody->AddForce(Vec2(0.f, -1000.f));
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
		m_RigidBody->AddForce(Vec2(0.f, 1000.f));
	}
	else if (KEY_TAP(KEY::DOWN))
	{
		//m_Animator->Play(L"WALK_DOWN", true);
	}
	else if (KEY_RELEASED(KEY::DOWN))
	{
		//m_Animator->Play(L"IDLE_DOWN", true);
	}



	// Space Ű�� ������ �̻����� ���.
	if (KEY_TAP(KEY::SPACE))
	{
		CMissile * pMissile = new CGuidedMissile;
		pMissile->SetName(L"Missile");

		Vec2 vMissilePos = GetPos();
		vMissilePos.y -= GetScale().y / 2.f;

		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(20.f, 20.f));

		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);

		LOG(LOG_TYPE::DBG_WARNING, L"�̻��� �߻�");
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

// Animation �߰�
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