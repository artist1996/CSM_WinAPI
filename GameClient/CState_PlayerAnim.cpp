#include "pch.h"
#include "CState_PlayerAnim.h"
#include "CAnimator.h"

CState_PlayerAnim::CState_PlayerAnim()
	: m_Animator(nullptr)
{
	m_Animator = GetObj()->GetComponent<CAnimator>();
}

CState_PlayerAnim::~CState_PlayerAnim()
{
}

void CState_PlayerAnim::Enter()
{
}

void CState_PlayerAnim::FinalTick()
{
	
}

void CState_PlayerAnim::Exit()
{
}
