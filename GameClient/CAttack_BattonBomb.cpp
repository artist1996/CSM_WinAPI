#include "pch.h"
#include "CAttack_BattonBomb.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CAnimation.h"
#include "CLevelMgr.h"
#include "CEffect_MonsterDead.h"

CAttack_BattonBomb::CAttack_BattonBomb()
	: m_Owner(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_bActive(false)
	, m_bPlay(false)
{
}

CAttack_BattonBomb::CAttack_BattonBomb(CObj* _Owner, bool _Active)
	: m_Owner(_Owner)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_bActive(_Active)
	, m_bPlay(false)
{
	// Info
	SetName(L"BattonBomb");
	SetPos(m_Owner->GetPos());
	SetScale(50.f, 60.f);
	
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	// Collider
	m_Collider->SetScale(GetScale());

	// Animation
	m_Animator->LoadAnimation(L"animation\\monster\\batton\\MISSILE.anim");

	m_Animator->Play(L"MISSILE", true);
}

CAttack_BattonBomb::~CAttack_BattonBomb()
{
}

void CAttack_BattonBomb::tick()
{	
	Vec2 vPos = GetPos();
	vPos += Vec2(0.f, 1.f) * 300.f * DT;

	SetPos(vPos);
}

void CAttack_BattonBomb::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"HitBox" == _OtherCollider->GetName())
	{
		Destroy();
		CEffect_MonsterDead* pEffect = new CEffect_MonsterDead(this);
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
	}
}
