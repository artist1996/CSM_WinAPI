#include "pch.h"
#include "CLevel_Loading.h"

#include "CLevelMgr.h"

#include "CTimeMgr.h"

#include "CLoading.h"

CLevel_Loading::CLevel_Loading()
	: m_Time(0.f)
{
}

CLevel_Loading::~CLevel_Loading()
{
}

void CLevel_Loading::tick()
{
	CLevel::tick();

	m_Time += DT;

	if (2.f <= m_Time)
	{
		if (L"SELECT" == CLevelMgr::GetInst()->GetPrevLevel()->GetName())
		{
			ChangeLevel(LEVEL_TYPE::STAGE_01);
		}

		else if (L"Stage01" == CLevelMgr::GetInst()->GetPrevLevel()->GetName())
		{
			ChangeLevel(LEVEL_TYPE::STAGE_02);
		}
		m_Time = 0.f;
	}
}

void CLevel_Loading::Enter()
{
	CLoading* pLoading = new CLoading;
	AddObject(LAYER_TYPE::UI, pLoading);

	CCamera::GetInst()->SetCameraLookAt(Vec2(400.f, 300.f));
}

void CLevel_Loading::Exit()
{
	DeleteAllObjects();
	m_Time = 0.f;

	if (L"Stage01" == CLevelMgr::GetInst()->GetPrevLevel()->GetName())
	{
		CCamera::GetInst()->SetCameraLookAt(Vec2(400.f, 940.f));
	}
}