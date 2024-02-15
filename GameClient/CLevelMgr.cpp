#include "pch.h"
#include "CLevelMgr.h"

#include "CCollisionMgr.h"

#include "CLevel.h"
#include "CLevel_Stage01.h"

#include "CPlayer.h"
#include "CMonster.h"

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
	pObject->SetPos(640.f, 384.f);
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


	// ���� �浹 �����ϱ�
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
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