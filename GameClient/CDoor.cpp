#include "pch.h"
#include "CDoor.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"
#include "CTexture.h"

#include "CPlatform_Level.h"

#include "CEffect_Door.h"

#include "CSound.h"

CDoor::CDoor()
	: m_Collider(nullptr)
	, m_Img(nullptr)
	, m_HP(0)
	, m_pSound(nullptr)
{
}

CDoor::CDoor(Vec2 _Pos, Vec2 _Scale, int _HP)
	: m_Collider(nullptr)
	, m_Img(nullptr)
	, m_HP(_HP)
	, m_pSound(nullptr)
{
	// Info
	SetName(L"Door");
	SetPos(_Pos);
	SetScale(_Scale);
	
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);

	// Collider
	m_Collider->SetOffsetPos(Vec2(110.f, 250.f));
	m_Collider->SetScale(Vec2(170.f, 300.f));
	
	// Texture
	m_Img = CAssetMgr::GetInst()->LoadTexture(L"Door", L"texture\\door.png");
	m_pSound = CAssetMgr::GetInst()->LoadSound(L"DESTROY_DOOR", L"sound\\level\\Door_Destroy.wav");
}

CDoor::~CDoor()
{
}

void CDoor::tick()
{
	CObj::tick();
	
	if (0 >= m_HP)
	{
		Destroy();
	}

	if (IsDead())
	{
		m_pSound->Play();
		CPlatform_Level* pPlatform = new CPlatform_Level(GetPos());
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLATFORM, pPlatform);

		CEffect_Door* pEffect = new CEffect_Door(Vec2(GetPos().x - 10.f, GetPos().y + 400.f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
		pEffect = new CEffect_Door(Vec2(GetPos().x + 150.f, GetPos().y + 350.f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
		pEffect = new CEffect_Door(Vec2(GetPos().x + 50.f, GetPos().y + 150.f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
		pEffect = new CEffect_Door(Vec2(GetPos().x + 200.f, GetPos().y + 200.f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pEffect);
		return;
	}
}

void CDoor::render()
{
	Vec2 vPos = GetRenderPos();
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)vPos.x
				 , (int)vPos.y
				 , m_Img->GetWidth()
				 , m_Img->GetHeight()
				 , m_Img->GetDC()
				 , 0, 0
				 , m_Img->GetWidth(), m_Img->GetHeight(), bf);
}

void CDoor::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (LAYER_TYPE::PLAYER_ATTACK == _OtherObj->GetLayerType())
	{
		--m_HP;
	}
}
