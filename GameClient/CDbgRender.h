#pragma once


class CDbgRender
{
	SINGLE(CDbgRender)
private:
	list<tDbgRenderInfo>	m_RenderList;
	list<tDbgLog>			m_LogList;
	bool					m_bRender;

	float					m_LogLife;
	int						m_LogSpace;
	Vec2					m_LogStartPos;



public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info)	{m_RenderList.push_back(_info);}
	void AddDbgLog(const tDbgLog& _info) { m_LogList.push_back(_info); }
	bool IsDbgRender() { return m_bRender; }

public:
	void tick();
	void render();
};


