#include "pch.h"
#include "CPlatform_Level.h"

#include "CCollider.h"

CPlatform_Level::CPlatform_Level()
	: m_Collider(nullptr)
{
}

CPlatform_Level::CPlatform_Level(Vec2 _Pos)
	: m_Collider(nullptr)
{
	// Info
	SetPos(_Pos);
	SetName(L"LEVEL_PLATFORM");
	
	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	
	// Collider
	m_Collider->SetOffsetPos(Vec2(100.f, 300.f));
	m_Collider->SetScale(Vec2(100.f, 100.f));
}

CPlatform_Level::~CPlatform_Level()
{
}


void CPlatform_Level::tick()
{
	CObj::tick();
}

void CPlatform_Level::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName())
	{
		ChangeLevel(LEVEL_TYPE::STAGE_02);
		return;
	}
}
