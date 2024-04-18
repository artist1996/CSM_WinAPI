#include "pch.h"
#include "CLevel_Stage02.h"

#include "CCollisionMgr.h"
#include "CPlayerEffectMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

#include "CStage02.h"

#include "CPlayer.h"

#include "CPlatform.h"

#include "CPlatform_Camera.h"

#include "CPlatform_BossRoom.h"

#include "CBoss.h"

#include "CUI_Ready.h"

#include "CDummy_Magma.h"

CLevel_Stage02::CLevel_Stage02()
	: m_pBGM(nullptr)
{
	SetName(L"Stage02");
}

CLevel_Stage02::~CLevel_Stage02()
{
	DeleteAllObjects();
}

void CLevel_Stage02::begin()
{
	CLevel::begin();


	m_pBGM = CAssetMgr::GetInst()->LoadSound(L"VOLCANO", L"sound\\level\\Volcano.wav");
	CSoundMgr::GetInst()->RegisterToBGM(m_pBGM);
	m_pBGM->SetVolume(20.f);
	m_pBGM->Play(true);
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

	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TRAP);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_MISSILE);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_ATTACK, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS_ATTACK);

	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"ZERO");
	//pPlayer->SetPos(Vec2(15517.f, 100.f));
	//pPlayer->SetPos(Vec2(15509.f, 460.f));
	pPlayer->SetPos(Vec2(200.f, 100.f));
	pPlayer->SetScale(Vec2(100.f, 100.f));

	AddObject(LAYER_TYPE::PLAYER, pPlayer);

	CPlayerEffectMgr::GetInst()->Init();

	CPlatform* pPlat = new CPlatform(Vec2(15887.f, 1070.f), Vec2(750.f, 50.f), LAYER_TYPE::PLATFORM);
	AddObject(LAYER_TYPE::PLATFORM, pPlat);
	
	CBoss* pBoss = new CBoss(Vec2(16393.f, 1270.f), 30);
	pBoss->SetTarget(pPlat);
	AddObject(LAYER_TYPE::BOSS, pBoss);

	CPlatform_BossRoom* pBossRoom = new CPlatform_BossRoom(Vec2(15882.f, 1041.f), Vec2(500.f, 500.f));
	
	AddObject(LAYER_TYPE::PLATFORM, pBossRoom);

	CUI* pReady = new CUI_Ready(Vec2(400.f, 950.f));
	AddObject(LAYER_TYPE::UI, pReady);

	CDummy_Magma* pMagma = new CDummy_Magma;
	AddObject(LAYER_TYPE::DUMMY, pMagma);

	LoadPlatform(L"platform\\platform.dat");
	LoadTrap(L"trap\\trap.dat");
	LoadMonster(L"monster\\monster.dat");


	CCamera::GetInst()->SetCameraLookAt(Vec2(400.f, 950.f));
	
	CCamera::GetInst()->SetMaxHighWidth(16050.f);
	CCamera::GetInst()->SetMaxLowWidth(400.f);
	CCamera::GetInst()->SetMaxHighHeight(1100.f);
	CCamera::GetInst()->SetMaxLowHeight(940.f);

	CPlatform_Camera* pPlatform = new CPlatform_Camera(Vec2(4914.f, 1169.f), Vec2(100.f, 1000.f), PLATFORM_CAMERA::LOW_WIDTH);
	AddObject(LAYER_TYPE::PLATFORM, pPlatform);
}

void CLevel_Stage02::Exit()
{
	DeleteAllObjects();
	CSoundMgr::GetInst()->RegisterToBGM(nullptr);
}