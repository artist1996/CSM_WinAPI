#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel*		m_pCurrentLevel;
	
public:
	void init();
	void progress();
	void render();

private:
	void ChangeLevel(LEVEL_TYPE _NextLevelType);

public:
	CObj* FindObjectByName(const wstring& _strName);

public:
	CLevel* GetCurrentLevel() { return m_pCurrentLevel; }

	friend class CTaskMgr;
};