#pragma once

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct CAM_EFFECT_INFO
{
	CAM_EFFECT	Effect;
	float		Duration;
	float		Time;
	float		Alpha;
};

class CObj;
class CTexture;

class CCamera
{
	SINGLE(CCamera)
private:
	CObj*					m_Owner;
	CTexture*				m_FadeTex;
	CTexture*				m_FadTex2;
	list<CAM_EFFECT_INFO>	m_EffectList;

	Vec2	   m_LookAt;
	Vec2	   m_Diff;
	float	   m_RespawnPos;

	float	   m_CamSpeed;

	float	   m_MaxHighHeight;
	float	   m_MaxLowHeight;

	float	   m_MaxHighWidth;
	float	   m_MaxLowWidth;

	bool	   m_DestroyBoss;

	bool	   m_EnterBoss;
	bool	   m_Return;

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return m_Diff + _RenderPos; }
	
	void SetOwner(CObj* _Owner) { m_Owner = _Owner; }
	
	void SetCameraEffect(CAM_EFFECT _Effect, float _Duration);

	void SetCameraLookAt(Vec2 _Pos) { m_LookAt = _Pos; }

	Vec2 GetLookAt() { return m_LookAt; }

	void SetMaxHighHeight(float _MaxHighHeight) { m_MaxHighHeight = _MaxHighHeight; }
	void SetMaxLowHeight(float _MaxLowHeight)   { m_MaxLowHeight = _MaxLowHeight; }
	void SetMaxHighWidth(float _MaxHighWidth)   { m_MaxHighWidth = _MaxHighWidth; }
	void SetMaxLowWidth(float _MaxLowWidth)     { m_MaxLowWidth = _MaxLowWidth; }

	void SetRespawnPos(float _Pos) { m_RespawnPos = _Pos; }
	
	void SetDestroyBoss(bool _boss) { m_DestroyBoss = _boss; }

	void SetCamSpeed(float _Speed) { m_CamSpeed = _Speed; }

	void SetEnterBoss(bool _Enter) { m_EnterBoss = _Enter; }
	void SetReturn(bool _Return)   { m_Return = _Return; }

	float GetRespawnPos() { return m_RespawnPos; }

public:
	void init();
	void tick();
	void render();

private:
	void Move();
	void CameraEffect();
};

