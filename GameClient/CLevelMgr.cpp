#include "pch.h"
#include "CLevelMgr.h"

#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLevel_Stage01.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CPlatform.h"

CLevelMgr::CLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{
}

CLevelMgr::~CLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);

	//for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	//{
	//	if (nullptr != m_arrLevel[i])
	//	{
	//		delete m_arrLevel[i];
	//	}
	//}
}


void CLevelMgr::init()
{
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new CLevel_Stage01;

	// ���� ���� ����
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// ������ ��ü �߰��ϱ�
	CObj* pObject = new CPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(100.f, 384.f);
	pObject->SetScale(100.f, 100.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pObject);

	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(800.f, 200.f);
	pObject->SetScale(100.f, 100.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);

	pObject = new CMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(100.f, 100.f);
	pObject->SetScale(100.f, 100.f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);

	//pObject = new CPlatform;
	//pObject->SetName(L"Platform");
	//pObject->SetPos(Vec2(640.f, 568.f));
	//pObject->SetScale(Vec2(500.f, 100.f));
	//m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);
	pObject = new CPlatform(Vec2(250.f, 718.f), Vec2(500.f, 100.f), LAYER_TYPE::PLATFORM);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);

	pObject = new CPlatform(Vec2(550.f, 718.f), Vec2(100.f, 500.f), LAYER_TYPE::PLATFORM);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);

	pObject = new CPlatform(Vec2(900.f, 718.f), Vec2(600.f, 100.f), LAYER_TYPE::PLATFORM);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);
	


	// ���� �浹 �����ϱ�
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLATFORM, LAYER_TYPE::PLAYER);

	m_pCurrentLevel->begin();
}

void CLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	// �����ȿ� �ִ� ��ü���� �������Ӹ��� ������ ������
	m_pCurrentLevel->tick();		// ������Ʈ�� ������ ����
	m_pCurrentLevel->finaltick();	// ������Ʈ�� ������ ����
}

void CLevelMgr::render()
{
	m_pCurrentLevel->render();
}