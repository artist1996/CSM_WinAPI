#include "pch.h"
#include "CEffect_Meteor.h"

#include "CRigidBody.h"

CEffect_Meteor::CEffect_Meteor()
	: m_RigidBody(nullptr)
	, m_Img(nullptr)
	, m_Type(METEOR_EFFECT::END)
	, m_Time(0.f)
{
}

CEffect_Meteor::CEffect_Meteor(Vec2 _Pos, METEOR_EFFECT _Type)
	: m_RigidBody(nullptr)
	, m_Img(nullptr)
	, m_Type(_Type)
	, m_Time(0.f)
{
	// Info
	SetPos(_Pos);

	// Component
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	
	// RigidBody
	m_RigidBody->UseGravity(true);

	// Texture
	if (METEOR_EFFECT::EFFECT_ONE == m_Type)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Meteor_Effect1", L"texture\\fragment\\Fragment1.png");
	}

	else if (METEOR_EFFECT::EFFECT_TWO == m_Type)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Meteor_Effect2", L"texture\\fragment\\Fragment2.png");
	}

	else if (METEOR_EFFECT::EFFECT_THREE == m_Type)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Meteor_Effect3", L"texture\\fragment\\Fragment3.png");
	}

	else if (METEOR_EFFECT::EFFECT_FOUR == m_Type)
	{
		m_Img = CAssetMgr::GetInst()->LoadTexture(L"Meteor_Effect4", L"texture\\fragment\\Fragment4.png");
	}
	
}

CEffect_Meteor::~CEffect_Meteor()
{
}

void CEffect_Meteor::tick()
{
	CObj::tick();

	Vec2 vPos = GetPos();

	m_Time += DT;

	if (1.5 <= m_Time)
		Destroy();

	if (METEOR_EFFECT::EFFECT_ONE == m_Type)
	{
		vPos += Vec2(-1.f, 0.f) * 200.f * DT;
	}

	else if (METEOR_EFFECT::EFFECT_TWO == m_Type)
	{
		vPos += Vec2(1.f, 0.f) * 200.f * DT;
	}

	else if (METEOR_EFFECT::EFFECT_THREE == m_Type)
	{
		vPos += Vec2(-1.f, -1.f) * 200.f * DT;
	}

	else if (METEOR_EFFECT::EFFECT_FOUR == m_Type)
	{
		vPos += Vec2(1.f, -1.f) * 200.f * DT;
	}

	SetPos(vPos);
}

void CEffect_Meteor::render()
{
	Vec2 vPos = GetRenderPos();
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 105;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC, (int)vPos.x
				 , (int)vPos.y
				 , m_Img->GetWidth()
				 , m_Img->GetHeight()
				 , m_Img->GetDC()
				 , 0, 0
				 , m_Img->GetWidth(), m_Img->GetHeight(), bf);
}