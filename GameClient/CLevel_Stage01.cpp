#include "pch.h"
#include "CLevel_Stage01.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CForce.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CMonster_Mettool.h"
#include "CMonster_Raiden.h"
#include "CMonster_GigaDeath.h"
#include "CPlatform.h"
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
	pObject->SetPos(400.f, 100.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);
	
	CMonster_Mettool* pMettool = new CMonster_Mettool(Vec2(400.f, 300.f), Vec2(50.f, 50.f), 1, 200.f);
	AddObject(LAYER_TYPE::MONSTER, pMettool);

	CMonster_Raiden* pRaiden = new CMonster_Raiden(Vec2(600.f, 300.f), Vec2(150.f, 180.f), 10, 200.f);
	AddObject(LAYER_TYPE::MONSTER, pRaiden);

	CMonster_GigaDeath* pGigaDeath = new CMonster_GigaDeath(Vec2(300.f, 300.f), Vec2(200.f, 180.f), 10, 200.f);
	AddObject(LAYER_TYPE::MONSTER, pGigaDeath);

	LoadPlatform(L"platform\\platform.dat");
	LoadLine(L"line\\line.dat");
	LoadMonster(L"monster\\monster.dat");

	// 레벨 충돌 설정하기
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::MONSTER);
	
}

void CLevel_Stage01::Exit()
{
	DeleteAllObjects();
}
