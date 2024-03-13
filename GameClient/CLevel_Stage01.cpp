#include "pch.h"
#include "CLevel_Stage01.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CForce.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"
#include "CLine.h"
#include "CPathMgr.h"


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
		// ���콺 ��ǥ �˾ƿ���
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
	// ������ ��ü �߰��ϱ�
	CObj* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(0.f, 0.f);
	pObject->SetScale(100.f, 100.f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	//pObject = new CMonster;
	//pObject->SetName(L"Monster");
	//pObject->SetPos(800.f, 200.f);
	//pObject->SetScale(100.f, 100.f);
	//AddObject(LAYER_TYPE::MONSTER, pObject);
	//
	//pObject = new CMonster;
	//pObject->SetName(L"Monster");
	//pObject->SetPos(100.f, 100.f);
	//pObject->SetScale(100.f, 100.f);
	//AddObject(LAYER_TYPE::MONSTER, pObject);

	LoadFromPlatform(L"platform\\platform.plat");
	LoadFromLine(L"line\\line.dat");

	// ���� �浹 �����ϱ�
	CCollisionMgr::GetInst()->CollisionCheckClear();
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::LINE, LAYER_TYPE::PLAYER);
}

void CLevel_Stage01::Exit()
{
	DeleteAllObjects();
}
