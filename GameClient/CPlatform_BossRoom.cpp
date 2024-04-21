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
		//CUI_Warning* pUI = new CUI_Warning;
		//pUI->SetPos(Vec2(GetPos().x + 50.f, 1100.f));
		////pUI->SetPos(400.f, 300.f);
		//pUI->SetTarget(CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Dragoon"));
		//SpawnObject(CLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::UI, pUI);
		CObj* pUI = CLevelMgr::GetInst()->FindObjectByName(L"WARNING_UI");
		static_cast<CUI_Warning*>(pUI)->Play();
		Destroy();
		CCamera::GetInst()->SetEnterBoss(true);
	}
}