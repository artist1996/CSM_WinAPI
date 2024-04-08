#include "pch.h"
#include "CLevel_Stage02.h"

#include "CCollisionMgr.h"

#include "CStage02.h"

#include "CPlayer.h"

#include "CPlatform_Camera.h"

#include "CPlatform_BossRoom.h"

CLevel_Stage02::CLevel_Stage02()
{
	SetName(L"Stage02");
}

CLevel_Stage02::~CLevel_Stage02()
{
}

void CLevel_Stage02::begin()
{
	CLevel::begin();
}

void CLevel_Stage02::tick()
{
	CLevel::tick();
}

void CLevel_Stage02::Enter()
{
	CObj* pBackGround = new CStage02;
	AddObject(LAYER_TYPE::BACKGROUND, pBackGround);

	CCollisionMgr::GetInst()->CollisionCheckClear();

	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"ZERO");
	pPlayer->SetPos(Vec2(200.f, 100.f));
	//pPlayer->SetPos(Vec2(15389.f, 460.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));

	AddObject(LAYER_TYPE::PLAYER, pPlayer);

	CPlatform_BossRoom* pBossRoom = new CPlatform_BossRoom(Vec2(15892.f, 1041.f), Vec2(500.f, 500.f));
	AddObject(LAYER_TYPE::PLATFORM, pBossRoom);

	LoadPlatform(L"platform\\platform.dat");
	LoadMonster(L"monster\\monster.dat");
	LoadTrap(L"trap\\trap.dat");


	CCamera::GetInst()->SetCameraLookAt(Vec2(400.f, 950.f));

	CCamera::GetInst()->SetMaxHighWidth(16353.f);
	CCamera::GetInst()->SetMaxLowWidth(400.f);
	CCamera::GetInst()->SetMaxHighHeight(1100.f);
	CCamera::GetInst()->SetMaxLowHeight(950.f);

	CPlatform_Camera* pPlatform = new CPlatform_Camera(Vec2(4914.f, 1169.f), Vec2(100.f, 1000.f), PLATFORM_CAMERA::LOW_WIDTH);
	AddObject(LAYER_TYPE::PLATFORM, pPlatform);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLATFORM);
}

void CLevel_Stage02::Exit()
{
	DeleteAllObjects();
}