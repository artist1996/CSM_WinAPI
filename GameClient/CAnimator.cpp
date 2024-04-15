#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
	: m_CurAnim(nullptr)
	, m_Repeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _Other)
	: CComponent(_Other)
	, m_CurAnim(nullptr)
	, m_Repeat(_Other.m_Repeat)
{
	for (const auto& pair : _Other.m_mapAnim)
	{
		CAnimation* pAnim = pair.second->Clone();
		pAnim->m_Animator = this;
		
		m_mapAnim.insert(make_pair(pair.first, pAnim));
	}

	if (nullptr != _Other.m_CurAnim)
		m_CurAnim = FindAnimation(_Other.m_CurAnim->GetName());
}

CAnimator::~CAnimator()
{
	Safe_Del_Map(m_mapAnim);
}

void CAnimator::finaltick()
{
	if (nullptr != m_CurAnim)
	{
		if (m_CurAnim->IsFinish() && m_Repeat)
		{
			m_CurAnim->Reset();
		}

		m_CurAnim->finaltick();
	}	
}

void CAnimator::render()
{
	if (nullptr != m_CurAnim)
		m_CurAnim->render();
}

void CAnimator::CreateAnimation(  const wstring& _AnimName
								, CTexture* _Atlas, Vec2 _StartPos, Vec2 _SliceSize
								, int _FrameCount, int _FPS)
{
	// 동일한 이름의 Animatio 이 이미 Animator 에 있는 경우
	CAnimation* pAnim = FindAnimation(_AnimName);
	assert(!pAnim);

	// Animation 객체 하나를 생성시킨다.
	pAnim = new CAnimation;
	pAnim->Create(_Atlas, _StartPos, _SliceSize, _FrameCount, _FPS);

	// Animation  이 Animator 에 등록되는 이름(키) 을 알게 한다.
	pAnim->SetName(_AnimName);

	// Animation 에 본인이 소속되는 Animator 를 알게 한다.
	pAnim->m_Animator = this;

	// Animator 가 Animation 을 Map 에 넣는다.
	m_mapAnim.insert(make_pair(_AnimName, pAnim));
}

void CAnimator::CreateAnimation(const wstring& _AnimName, CTexture* _Atlas, vector<tAnimFrm> _vecFrame)
{
	CAnimation* pAnim = FindAnimation(_AnimName);

	if (nullptr != pAnim)
	{
		m_mapAnim.erase(pAnim->GetName());
		delete pAnim;
	}
	
	pAnim = new CAnimation;
	pAnim->Create(_Atlas, _vecFrame);
	
	pAnim->SetName(_AnimName);
	
	pAnim->m_Animator = this;

	m_mapAnim.insert(make_pair(_AnimName, pAnim));
	m_CurAnim = pAnim;
}

void CAnimator::LoadAnimation(const wstring& _strRelativeFilePath)
{
	CAnimation* pAnim = new CAnimation;
	if (FAILED(pAnim->Load(_strRelativeFilePath)))
	{
		delete pAnim;
		return;
	}

	if (nullptr != FindAnimation(pAnim->GetName()))
	{
		delete pAnim;
		return;
	}

	pAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
}

void CAnimator::LoadToolAnimation(const wstring& _strFullPath)
{
	CAnimation* pAnim = new CAnimation;
	if (FAILED(pAnim->LoadAnimation(_strFullPath)))
	{
		delete pAnim;
		return;
	}

	if (nullptr != FindByAnimationName(pAnim->GetName()))
	{
		delete pAnim;
		return;
	}

	pAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));
	m_CurAnim = pAnim;
}


CAnimation* CAnimator::FindAnimation(const wstring& _AnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_AnimName);

	if (iter == m_mapAnim.end())
		return nullptr;
	
	return iter->second;
}

CAnimation* CAnimator::FindByAnimationName(const wstring& _AnimName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_AnimName);
	
	if (iter == m_mapAnim.end())
		return nullptr;

	m_CurAnim = iter->second;

	return iter->second;
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
	m_CurAnim = FindAnimation(_AnimName);

	if (nullptr == m_CurAnim)
		return;

	m_CurAnim->Reset();
	m_Repeat = _Repeat;
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat, int _Idx)
{
	m_CurAnim = FindAnimation(_AnimName);
	m_CurAnim->Reset(_Idx);
	m_Repeat = _Repeat;
}