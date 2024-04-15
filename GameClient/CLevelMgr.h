#pragma once

class CLevel;

class CLevelMgr
{
	SINGLE(CLevelMgr)
private:
	CLevel*		m_arrLevel[(UINT)LEVEL_TYPE::END];
	CLevel*		m_pCurrentLevel;
	CLevel*		m_pPrevLevel;
	
public:
	void init();
	void progress();
	void render();

	void SetPrevLevel(CLevel* _Level) { m_pPrevLevel = _Level; }

private:
	void ChangeLevel(LEVEL_TYPE _NextLevelType);

public:
	CObj* FindObjectByName(const wstring& _strName);

public:
	CLevel* GetCurrentLevel() { return m_pCurrentLevel; }
	CLevel* GetPrevLevel()	  { return m_pPrevLevel; }
	friend class CTaskMgr;
};