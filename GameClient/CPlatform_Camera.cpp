#include "pch.h"
#include "CPlatform_Camera.h"

#include "CCollider.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CPlatform_Camera::CPlatform_Camera()
	: m_Collider(nullptr)
	, m_Type(PLATFORM_CAMERA::END)
{
}

CPlatform_Camera::CPlatform_Camera(Vec2 _Pos, Vec2 _Scale, PLATFORM_CAMERA _Type)
	: m_Collider(nullptr)
	, m_Type(_Type)
{
	// Info
	SetPos(_Pos);
	SetScale(_Scale);

	// Component
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(GetScale());
}

CPlatform_Camera::~CPlatform_Camera()
{
}

void CPlatform_Camera::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (L"Stage01" == CLevelMgr::GetInst()->GetCurrentLevel()->GetName()
		&& L"ZERO" == _OtherObj->GetName())
	{
		switch (m_Type)
		{
		case PLATFORM_CAMERA::MAX_HEIGHT:
		{
			CCamera::GetInst()->SetMaxHighHeight(1293.f);
			CCamera::GetInst()->SetCamSpeed(6000.f);
			Destroy();
		}
		break;

		case PLATFORM_CAMERA::MAX_HEIGHT2:
		{
			CCamera::GetInst()->SetMaxHighHeight(300.f);
			CCamera::GetInst()->SetCamSpeed(6000.f);
			Destroy();
		}
		break;
		}
	}
	else if (L"Stage02" == CLevelMgr::GetInst()->GetCurrentLevel()->GetName()
		&& L"ZERO" == _OtherObj->GetName())
	{
		switch (m_Type)
		{
		case PLATFORM_CAMERA::MAX_HEIGHT:
		{
			Destroy();
		}
		break;

		case PLATFORM_CAMERA::MAX_WIDTH:
		{
			Destroy();
		}
		break;

		case PLATFORM_CAMERA::LOW_HEIGHT:
		{
			Destroy();
		}
		break;

		case PLATFORM_CAMERA::LOW_WIDTH:
		{
			CCamera::GetInst()->SetMaxLowWidth(4694.f);
			CCamera::GetInst()->SetMaxHighHeight(297.f);
			Destroy();
		}
		break;
		}
	}
}

void CPlatform_Camera::OnOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}

void CPlatform_Camera::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
}