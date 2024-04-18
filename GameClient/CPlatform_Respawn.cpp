#include "pch.h"
#include "CPlatform_Respawn.h"
#include "CCollider.h"

CPlatform_Respawn::CPlatform_Respawn()
{
}

CPlatform_Respawn::CPlatform_Respawn(Vec2 _Pos, Vec2 _Scale)
	: m_Collider(nullptr)
{
	SetPos(_Pos);
	SetScale(_Scale);

	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());

}

CPlatform_Respawn::~CPlatform_Respawn()
{
}

void CPlatform_Respawn::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"ZERO" == _OtherObj->GetName())
	{
		Destroy();
		_OtherObj->SetRespawnPos(Vec2(GetPos().x, GetPos().y - 300.f));
		CCamera::GetInst()->SetRespawnPos(GetPos().y - 200.f);
		return;
	}
}
