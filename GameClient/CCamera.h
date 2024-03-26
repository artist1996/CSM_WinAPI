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
	list<CAM_EFFECT_INFO>	m_EffectList;

	Vec2	   m_LookAt;
	Vec2	   m_Diff;
	float	   m_CamSpeed;

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return m_Diff + _RenderPos; }
	
	void SetOwner(CObj* _Owner) { m_Owner = _Owner; }
	
	void SetCameraEffect(CAM_EFFECT _Effect, float _Duration);

public:
	void init();
	void tick();
	void render();

private:
	void Move();
	void CameraEffect();
};

