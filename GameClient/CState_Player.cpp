#include "pch.h"
#include "CState_Player.h"

CState_Player::CState_Player()
	: m_Rigidbody(nullptr)
	, m_Animator(nullptr)
	, m_Collider(nullptr)
	, m_HitBox(nullptr)
{
}

CState_Player::~CState_Player()
{
}