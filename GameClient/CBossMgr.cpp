#include "pch.h"
#include "CBossMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAttack_Hadouken.h"

CBossMgr::CBossMgr()
{}

CBossMgr::~CBossMgr()
{}

void CBossMgr::init()
{
	CObj* pOwner = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Dragoon");

}

void CBossMgr::tick()
{
	if (m_ActiveBreath)
	{

	}
}

void CBossMgr::ActiveByBreath()
{
}
