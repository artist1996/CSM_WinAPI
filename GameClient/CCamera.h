#pragma once
class CCamera
{
	SINGLE(CCamera)
private:
	Vec2 m_LookAt;
	Vec2 m_Diff;

	float m_CamSpeed;

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_Diff; }


public:
	void init();
	void tick();
};

