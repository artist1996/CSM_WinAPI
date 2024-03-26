#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr)
private:
	CUI*	m_FocusedUI;	// 포커싱된 UI 를 가리킨다.

public:
	CUI* GetFocusedUI() { return m_FocusedUI; }

public:
	void tick();

private:
	CUI* GetPriorityUI(CUI* _UI);
	void ChangeFocusedUI(CUI* _UI);
};

