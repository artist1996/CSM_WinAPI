#include "pch.h"
#include "CDummy_Select.h"

#include "CAnimator.h"
#include "CAnimation.h"

CDummy_Select::CDummy_Select()
	: m_Animator(nullptr)
	, m_Type(0)
	, m_Move(false)
{
}

CDummy_Select::CDummy_Select(Vec2 _Pos, int _Type)
	: m_Animator(nullptr)
	, m_Type(_Type)
{
	SetPos(_Pos);
	
	m_Animator = (CAnimator*)AddComponent(new CAnimator);

	if (0 == m_Type)
	{
		m_Animator->LoadAnimation(L"animation\\player\\X\\IDLE.anim");
		m_Animator->LoadAnimation(L"animation\\player\\X\\SHOOT.anim");
		m_Animator->LoadAnimation(L"animation\\player\\X\\RECALL.anim");

		m_Animator->Play(L"IDLE", true);
	}

	else if (1 == m_Type)
	{
		m_Animator->LoadAnimation(L"animation\\player\\left\\IDLE_LEFT.anim");
		m_Animator->LoadAnimation(L"animation\\player\\left\\ATTACK01_LEFT_DUMMY.anim");
		m_Animator->LoadAnimation(L"animation\\player\\left\\VICTORY_LEFT_DUMMY.anim");

		m_Animator->Play(L"IDLE_LEFT", true);
	}
}

CDummy_Select::~CDummy_Select()
{
}


void CDummy_Select::tick()
{
	if (0 == m_Type && L"RECALL" == m_Animator->GetCurAnim()->GetName() && m_Animator->GetCurAnim()->IsFinish())
	{
		Vec2 vPos = GetPos();
		vPos += Vec2(0.f, -1.f) * 1000.f * DT;
		
		SetPos(vPos);
	}

	else if (1 == m_Type && L"VICTORY_LEFT_DUMMY" == m_Animator->GetCurAnim()->GetName() && m_Animator->GetCurAnim()->IsFinish())
	{
		Vec2 vPos = GetPos();
		vPos += Vec2(0.f, -1.f) * 1000.f * DT;

		SetPos(vPos);
	}
}

void CDummy_Select::Play(const wstring& _strName, bool _Repeat)
{
	m_Animator->Play(_strName, _Repeat);
}