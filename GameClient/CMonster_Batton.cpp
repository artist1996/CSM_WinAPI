#include "pch.h"
#include "CMonster_Batton.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CFSM.h"

#include "CBatton_Idle.h"
#include "CBatton_Move.h"
#include "CBatton_Attack.h"

CMonster_Batton::CMonster_Batton()
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
	, m_BombImg(nullptr)
{
}

CMonster_Batton::CMonster_Batton(Vec2 _Pos, Vec2 _Scale, int _HP, float _DetectRange)
	: m_Collider(nullptr)
	, m_Animator(nullptr)
	, m_FSM(nullptr)
	, m_BombImg(nullptr)
	, m_Bomb(true)
{
	// Info
	SetPos(_Pos);
	SetScale(_Scale);
	SetHP(_HP);
	SetDetectRange(_DetectRange);
	SetDirection(DIRECTION::LEFT);
	SetID(OBJ_ID::BATTON);

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// Collider
	m_Collider->SetOffsetPos(Vec2(0.f, -40.f));
	m_Collider->SetScale(_Scale);

	// Animation
	m_Animator->LoadAnimation(L"animation\\monster\\batton\\IDLE.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\batton\\ATTACK.anim");

	// FSM
	m_FSM->AddState(L"IDLE", new CBatton_Idle);
	m_FSM->AddState(L"MOVE", new CBatton_Move);
	m_FSM->AddState(L"ATTACK", new CBatton_Attack);

	// Texture
	m_BombImg = CAssetMgr::GetInst()->LoadTexture(L"Bomb",L"texture\\Bomb.png");
}

CMonster_Batton::~CMonster_Batton()
{
}

void CMonster_Batton::begin()
{
	CObj::begin();
	
	CObj* pTarget = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ZERO");
	
	m_FSM->SetBlackboardData(L"Target", DATA_TYPE::OBJECT, pTarget);
	

	m_FSM->ChangeState(L"IDLE");
}

void CMonster_Batton::render()
{
	CObj::render();

	if (m_Bomb)
	{
		Vec2 vPos = GetRenderPos();

		BLENDFUNCTION bf = {};

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(DC
			, (int)(vPos.x - 15.f)
			, (int)(vPos.y - 25.f)
			, m_BombImg->GetWidth(), m_BombImg->GetHeight()
			, m_BombImg->GetDC()
			, 0, 0
			, m_BombImg->GetWidth(), m_BombImg->GetHeight(), bf);
		return;

	}
}
