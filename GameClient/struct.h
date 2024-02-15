#pragma once

struct Vec2
{
public:
	float x;
	float y;

public:
	float GetDistance(Vec2 _Other)
	{
		return sqrtf(powf(x - _Other.x, 2) + powf(y - _Other.y, 2));
	}


	Vec2 operator +(float f) { return Vec2(x + f, y + f); }
	Vec2 operator -(float f) { return Vec2(x - f, y - f); }
	Vec2 operator *(float f) { return Vec2(x * f, y * f); }
	Vec2 operator /(float f) { assert(f); return Vec2(x / f, y / f); }

	Vec2 operator + (Vec2 _Other) { return Vec2(x + _Other.x, y + _Other.y); }
	Vec2 operator - (Vec2 _Other) { return Vec2(x - _Other.x, y - _Other.y); }
	Vec2 operator * (Vec2 _Other) { return Vec2(x * _Other.x, y * _Other.y); }
	Vec2 operator / (Vec2 _Other) { assert(!(0.f == _Other.x || 0.f == _Other.y)); return Vec2(x / _Other.x, y / _Other.y); }


	void operator +=(float _f)
	{
		x += _f;
		y += _f;
	}

	void operator +=(Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}


public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	~Vec2()
	{

	}
};

struct tDbgRenderInfo
{
	DBG_SHAPE	Shape;
	Vec2		Position;
	Vec2		Scale;
	PEN_TYPE	Color;

	float		Duration;
	float		Age;
};

struct tDbgLog
{
	LOG_TYPE	Type;		// �α��� ����
	wstring		strLog;		// �α� �޼���
	float		Age;		// �αװ� ��µ� �ð�
};


struct tTask
{
	TASK_TYPE	Type;
	DWORD_PTR	Param1;
	DWORD_PTR	Param2;
	DWORD_PTR	Param3;
};