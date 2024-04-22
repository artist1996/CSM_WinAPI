#include "pch.h"
#include "CLevel_Stage01.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CPlayerEffectMgr.h"
#include "CLevelMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

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
#include "CPlatform_Respawn.h"
#include "CLine.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CStage01.h"

#include "CDoor.h"
#include "CPlayerEffectMgr.h"

#include "CUI_Ready.h"

CLevel_Stage01::CLevel_Stage01()
	: m_pBGM(nullptr)
	, m_Time(0.f)
	, m_Ready(true)
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

	m_pBGM = CAssetMgr::GetInst()->LoadSound(L"VOLCANO", L"sound\\level\\Volcano.wav");
	CSoundMgr::GetInst()->RegisterToBGM(m_pBGM);
	m_pBGM->SetVolume(20.f);
	m_pBGM->Play(true);
}

void CLevel_Stage01::tick()
{
	CLevel::tick();

	if (m_Ready)
		m_Time += DT;

	if (1.f <= m_Time)
	{
		CUI* pReadyUI = new CUI_Ready(Vec2(400.f, 400.f));
		AddObject(LAYER_TYPE::UI, pReadyUI);
		m_Ready = false;
		m_Time = 0.f;
	}

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
	pObject->SetLife(2);
	pObject->SetName(L"ZERO");
	//pObject->SetPos(18236.f, 0.f);
	pObject->SetPos(400.f, 0.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	CPlayerEffectMgr::GetInst()->Init();
	
	CTrap_Eruption* pEruption = new CTrap_Eruption(Vec2(9787.f, 1439.f), OBJ_ID::ERUPTION);
	AddObject(LAYER_TYPE::TRAP, pEruption);

	//Camera
	CPlatform_Respawn* pRespawn = new CPlatform_Respawn(Vec2(3651.f, 1437.f), Vec2(300.f, 300.f));
	AddObject(LAYER_TYPE::PLATFORM, pRespawn);
	CPlatform_Camera* pPlatform = new CPlatform_Camera(Vec2(3751.f, 1437.f), Vec2(300.f, 300.f), PLATFORM_CAMERA::MAX_HEIGHT);
	AddObject(LAYER_TYPE::PLATFORM, pPlatform);
	pPlatform = new CPlatform_Camera(Vec2(16291.f, 1441.f), Vec2(300.f, 300.f), PLATFORM_CAMERA::MAX_HEIGHT2);
	AddObject(LAYER_TYPE::PLATFORM, pPlatform);

	CCamera::GetInst()->SetCameraLookAt(Vec2(400.f, 400.f));
	CCamera::GetInst()->SetMaxHighWidth(18751.f);
	CCamera::GetInst()->SetMaxLowWidth(400.f);
	CCamera::GetInst()->SetMaxHighHeight(200.f);
	CCamera::GetInst()->SetMaxLowHeight(1236.f);
	CCamera::GetInst()->SetCamSpeed(1000.f);

	

	// Load
	LoadPlatform(L"platform\\platform.dat");
	LoadLine(L"line\\line.dat");
	LoadMonster(L"monster\\monster.dat");
	LoadTrap(L"trap\\trap.dat");
	LoadDeathPlatform(L"platform\\death.dat");

	CDoor* pDoor = new CDoor(Vec2(18936.f, 214.f), Vec2(100.f, 100.f), 10);
	AddObject(LAYER_TYPE::TRAP, pDoor);
	
	// 레벨 충돌 설정하기
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_ATTACK, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_MISSILE, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_MISSILE, LAYER_TYPE::LINE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_ATTACK, LAYER_TYPE::TRAP);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::EFFECT);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_MISSILE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TRAP);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::TRAP, LAYER_TYPE::LINE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

	CLevelMgr::GetInst()->SetPrevLevel(this);
}

void CLevel_Stage01::Exit()
{
	DeleteAllObjects();
	CPlayerEffectMgr::GetInst()->clear();
	CSoundMgr::GetInst()->RegisterToBGM(nullptr);
}
