#pragma once

class CAfterImage;

class CShadowMgr
{
	SINGLE(CShadowMgr)

private:
	vector<CAfterImage*> m_vecShadow;

public:
	void Init();
	void Play(const wstring& _strName, bool _Play);
	void SetActive(bool _Active);
	bool GetActive();
	void clear() { m_vecShadow.clear(); }
};

