#include "pch.h"
#include "CLevel_Stage01.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CForce.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"


CLevel_Stage01::CLevel_Stage01()
{
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
	CObj* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(100.f, 384.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(800.f, 200.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::MONSTER, pObject);

	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(100.f, 100.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::MONSTER, pObject);

	//pObject = new CPlatform;
	//pObject->SetName(L"Platform");
	//pObject->SetPos(Vec2(640.f, 568.f));
	//pObject->SetScale(Vec2(500.f, 100.f));
	//m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);
	pObject = new CPlatform(Vec2(250.f, 718.f), Vec2(500.f, 100.f), LAYER_TYPE::PLATFORM);
	AddObject(LAYER_TYPE::PLATFORM, pObject);

	pObject = new CPlatform(Vec2(550.f, 718.f), Vec2(100.f, 500.f), LAYER_TYPE::PLATFORM);
	AddObject(LAYER_TYPE::PLATFORM, pObject);

	pObject = new CPlatform(Vec2(900.f, 718.f), Vec2(600.f, 100.f), LAYER_TYPE::PLATFORM);
	AddObject(LAYER_TYPE::PLATFORM, pObject);


	// 레벨 충돌 설정하기
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLATFORM, LAYER_TYPE::PLAYER);
}

void CLevel_Stage01::Exit()
{
	DeleteAllObjects();
}
