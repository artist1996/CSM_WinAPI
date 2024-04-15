#pragma once

class CAttack_Hadouken;
class CAttack_Breath;

class CBossMgr
{
	SINGLE(CBossMgr);
private:
	vector<CAttack_Breath*>	  m_vecBreath;
	size_t					  m_Count;

	float				      m_Time;

	bool					  m_ActiveBreath;

public:
	void SetActiveBreath(bool _Active)   { m_ActiveBreath = _Active; }
	void ActiveByBreath();

public:
	void init();
	void tick();
};

