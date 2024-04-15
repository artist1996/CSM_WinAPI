#pragma once

class CAfterImage;
class CEffect_Dash;
class CEffect_Kick;

class CPlayerEffectMgr
{
	SINGLE(CPlayerEffectMgr)

private:
	vector<CEffect_Dash*> m_vecDash;
	vector<CEffect_Kick*>  m_vecKick;
	vector<CAfterImage*>  m_vecShadow;

	size_t				  m_DashCount;
	size_t				  m_KickCount;

public:
	void Init();
	void tick();
public:
	void Play(const wstring& _strName, bool _Play);
	void PlayDash(const wstring& _strName, bool _Play);
	void DashSetPos(Vec2 _Pos);

	void KickSetPos(Vec2 _Pos);
	void PlayKick(const wstring& _strName, bool _Play);

	void ChangeCurAnim(const wstring& _strName);

	void SetActive(bool _Active);
	bool GetActive();
	void clear();
};

