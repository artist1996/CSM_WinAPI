#include "pch.h"
#include "CLevel_Stage01.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"

#include "CPlayer.h"
#include "CForce.h"

#include "CMonster.h"
#include "CMonster_Mettool.h"
#include "CMonster_Raiden.h"
#include "CMonster_GigaDeath.h"
#include "CMonster_Batton.h"

#include "CTrap_Meteor.h"
#include "CTrap_Eruption.h"

#include "CPlatform.h"
#include "CPlatform_Camera.h"
#include "CLine.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CStage01.h"

CLevel_Stage01::CLevel_Stage01()
{
	SetName(L"Stage01");
}

CLevel_Stage01::~CLevel_Stage01()
{
	DeleteAllObjects();
}

void CLevel_Stage01::begin()
{
	CLevel::begin();
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 5.f);
}

void CLevel_Stage01::tick()
{
	CLevel::tick();

	if (KEY_TAP(KEY::LBTN))
	{
		// 마우스 좌표 알아오기
		Vec2 vMousePos = CKeyMgr::GetInst()->GetInst()->GetMousePos();

		CForce* pForce = new CForce;
		pForce->SetPos(vMousePos);
		pForce->SetForce(500.f, 300.f, 0.3f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}

void CLevel_Stage01::Enter()
{
	// 레벨에 물체 추가하기
	
	CObj* pBackGround = new CStage01;
	AddObject(LAYER_TYPE::BACKGROUND, pBackGround);
	
	CEngine::GetInst()->ChangeWindowSize(Vec2(800.f, 600.f), false);
	// Player
	CObj* pObject = new CPlayer;
	pObject->SetName(L"ZERO");
	pObject->SetPos(400.f, 0.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);
	
	//CMonster_Mettool* pMettool = new CMonster_Mettool(Vec2(400.f, 300.f), Vec2(50.f, 50.f), 1, 200.f);
	//AddObject(LAYER_TYPE::MONSTER, pMettool);
	//
	//CMonster_Raiden* pRaiden = new CMonster_Raiden(Vec2(600.f, 300.f), Vec2(150.f, 180.f), 10, 200.f);
	//AddObject(LAYER_TYPE::MONSTER, pRaiden);
	//
	//CMonster_GigaDeath* pGigaDeath = new CMonster_GigaDeath(Vec2(300.f, 300.f), Vec2(200.f, 180.f), 5, 200.f);
	//AddObject(LAYER_TYPE::MONSTER, pGigaDeath);

	//CMonster_Batton* pBatton = new CMonster_Batton(Vec2(900.f, 300.f), Vec2(50.f, 70.f), 1, 200.f);
	//AddObject(LAYER_TYPE::MONSTER, pBatton);
	//
	//CTrap_Meteor* pMeteor = new CTrap_Meteor(Vec2(900.f, 300.f), OBJ_ID::METEOR_UP);
	//AddObject(LAYER_TYPE::TRAP, pMeteor);
	//
	//CTrap_Eruption* pEruption = new CTrap_Eruption(Vec2(500.f, 400.f), OBJ_ID::ERUPTION);
	//AddObject(LAYER_TYPE::TRAP, pEruption);
	//
	//pMeteor = new CTrap_Meteor(Vec2(1100.f, 300.f), OBJ_ID::METEOR_DOWN);
	//AddObject(LAYER_TYPE::TRAP, pMeteor);

	//Camera
	CPlatform_Camera* pPlatform = new CPlatform_Camera(Vec2(3751.f, 1437.f), Vec2(300.f, 300.f), PLATFORM_CAMERA::MAX_HEIGHT);
	AddObject(LAYER_TYPE::PLATFORM, pPlatform);
	pPlatform = new CPlatform_Camera(Vec2(16291.f, 1441.f), Vec2(300.f, 300.f), PLATFORM_CAMERA::MAX_HEIGHT2);
	AddObject(LAYER_TYPE::PLATFORM, pPlatform);
	
	CCamera::GetInst()->SetMaxHighWidth(18751.f);
	CCamera::GetInst()->SetMaxLowWidth(400.f);
	CCamera::GetInst()->SetMaxHighHeight(300.f);
	CCamera::GetInst()->SetMaxLowHeight(1236.f);


	// Load
	LoadPlatform(L"platform\\platform.dat");
	LoadLine(L"line\\line.dat");
	LoadMonster(L"monster\\monster.dat");
	LoadTrap(L"trap\\trap.dat");
	
	// 레벨 충돌 설정하기
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_MISSILE, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_MISSILE, LAYER_TYPE::LINE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::MONSTER);
}

void CLevel_Stage01::Exit()
{
	DeleteAllObjects();
}
