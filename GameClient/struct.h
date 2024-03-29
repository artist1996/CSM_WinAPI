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

	float Length()
	{
		return sqrtf((x * x) + (y * y));
	}

	void Normalize()
	{
		assert(!(x == 0.f && y == 0.f));
		float Len = Length();
		
		x /= Len;
		y /= Len;
	}

	bool IsZero() { return x == 0.f && y == 0.f; }


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
	void operator -=(float _f)
	{
		x -= _f;
		y -= _f;
	}
	void operator *=(float _f)
	{
		x *= _f;
		y *= _f;
	}
	void operator /=(float _f)
	{
		assert(_f);
		x /= _f;
		y /= _f;
	}

	void operator +=(Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}

	void operator -=(Vec2 _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
	}
	void operator *=(Vec2 _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
	}

	void operator /=(Vec2 _Other)
	{
		assert(_Other.x && _Other.y);

		x /= _Other.x;
		y /= _Other.y;
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

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
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
	LOG_TYPE	Type;		// 로그의 종류
	wstring		strLog;		// 로그 메세지
	float		Age;		// 로그가 출력된 시간
};


struct tTask
{
	TASK_TYPE	Type;
	DWORD_PTR	Param1;
	DWORD_PTR	Param2;
	DWORD_PTR	Param3;
};

struct tInfo
{
	Vec2 StartPos;
	Vec2 EndPos;
};

struct tAnimFrm
{
	Vec2    StartPos;
	Vec2    SliceSize;
	Vec2    Offset;
	float   Duration;

	tAnimFrm()
		: Duration(0.f)
	{}
};

struct CUT_INFO
{
	Vec2 Start;
	Vec2 End;

	CUT_INFO()
		: Start{}
		, End{}
	{}

	CUT_INFO(Vec2 _Start, Vec2 _End)
		: Start(_Start)
		, End(_End)
	{}

};