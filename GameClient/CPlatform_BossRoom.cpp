#include "pch.h"
#include "CPlatform_BossRoom.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCollider.h"

#include "CUI_Warning.h"

CPlatform_BossRoom::CPlatform_BossRoom()
	: m_Collider(nullptr)
{
}

CPlatform_BossRoom::CPlatform_BossRoom(Vec2 _Pos, Vec2 _Scale)
	: m_Collider(nullptr)
{
	// Info
	SetPos(_Pos);
	SetScale(_Scale);

	// Collider
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(_Scale);
}

CPlatform_BossRoom::~CPlatform_BossRoom()
{
}

void CPlatform_BossRoom::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName())
	{
		CUI_Warning* pUI = new CUI_Warning;
		pUI->SetPos(Vec2(GetPos().x, 1100.f));
		SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::DUMMY, pUI);
		Destroy();
	}
}