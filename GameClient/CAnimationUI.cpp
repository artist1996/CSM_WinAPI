#include "pch.h"
#include "CAnimationUI.h"
#include "CDummy.h"

CAnimationUI::CAnimationUI()
	: m_DummyObject(nullptr)
	, m_Repeat(false)
{
	SetName(L"ANIMATIONUI");
}

CAnimationUI::~CAnimationUI()
{

}

void CAnimationUI::begin()
{
	m_DummyObject = new CDummy;
	m_DummyObject->SetOwnerUI(this);
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	float x = (vPos.x + vScale.x) - vPos.x * 0.5f;
	float y = (vPos.y + vScale.y)  * 0.5f;

	m_DummyObject->SetPos(Vec2(x, y));
	m_DummyObject->SetScale(Vec2(1.f, 1.f));
}

void CAnimationUI::render_ui()
{
	CUI::render_ui();
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	USE_PEN(DC, PEN_TYPE::PEN_BLACK);
	Rectangle(DC, (int)vPos.x, (int)vPos.y, (int)(vPos.x + vScale.x), (int)(vPos.y + vScale.y));
}


void CAnimationUI::PlayAnimation(const wstring& _strName, bool _Repeat)
{
	SetPlay(_strName, _Repeat);
	m_DummyObject->PlayAnimation(_strName, _Repeat);
}

CAnimator* CAnimationUI::GetAnimator()
{
	return m_DummyObject->GetAnimator();
}

void CAnimationUI::CreateAnimation(const wstring& _strName,const vector<tAnimFrm>& _vecFrm, CTexture* _Img)
{
	m_DummyObject->CreateAnimation(_strName, _vecFrm, _Img);
}

void CAnimationUI::SaveAnimation(const wstring& _RelativeFilePath)
{
	m_DummyObject->SaveAnimation(_RelativeFilePath);
}

void CAnimationUI::LoadAnimation(const wstring& _strKey)
{
	m_DummyObject->LoadAnimation(_strKey);
}

void CAnimationUI::tick_ui()
{
}

void CAnimationUI::InitAnimation(const wstring& _strKey)
{
	m_DummyObject->InitAnimation(_strKey);
}

void CAnimationUI::Reset()
{
	m_DummyObject->ResetAnimation();
}
