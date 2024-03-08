#include "pch.h"
#include "CTileMap.h"
#include "CTexture.h"
#include "CDbgRender.h"

CTileMap::CTileMap()
	: m_AtlasTex(nullptr)
	, m_TileSize(Vec2(TILE_SIZE, TILE_SIZE))
	, m_Row(1)
	, m_Col(1)
	, m_MaxImgRow(0)
	, m_MaxImgCol(0)
{
}

CTileMap::~CTileMap()
{
}

void CTileMap::finaltick()
{
}

void CTileMap::render()
{
	render_tile();

	if (CDbgRender::GetInst()->IsDbgRender())
	{
		render_grid();
	}
}

void CTileMap::SetRow(UINT _Row)
{
	m_Row = _Row;

	// vector�� clear �����ְ� 1���� ������ �࿭ ������ ������ش�.
	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void CTileMap::SetCol(UINT _Col)
{
	m_Col = _Col;

	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void CTileMap::SetRowCol(UINT _Row, UINT _Col)
{
	m_Row = _Row;
	m_Col = _Col;

	m_vecTileInfo.clear();
	m_vecTileInfo.resize(m_Row * m_Col);
}

void CTileMap::SetAtlasTex(CTexture* _Atlas)
{
	m_AtlasTex = _Atlas;
	
	if (m_AtlasTex)
	{
		// �� �ִ� �� �� ���
		// TileSize�� 64 x 64�� ������� ������ �ش� Tile�� Atlas ���� ���� ��ġ�� 64�� �������ָ� �ִ� �࿭ ������ �����Եȴ�.
		m_MaxImgRow = m_AtlasTex->GetHeight() / m_TileSize.y;
		m_MaxImgCol = m_AtlasTex->GetWidth() / m_TileSize.x;
	}
}

void CTileMap::render_grid()
{
	Vec2 vRenderPos = GetOwner()->GetRenderPos();
	
	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);
	
	for (UINT i = 0; i < m_Row; ++i)
	{
		for (UINT j = 0; j < m_Col; ++j)
		{
			// �簢�� �׸��µ� �»���� �� ���� Render Position x�� Tile�� ����� j(��)�� �����ְ� �����ش�.
			// �»�� y Position�� ��(i)�� �����ش�.
			// ���ϴ��� Render Position�� Tile�� ����� ���� ���ؼ� ������ ���� Ÿ���� ����� �ѹ� �� �����ش�.
			// ���ϴ� y Position�� ���� �����ְ� Tile�� ����� �����ش�.
			Rectangle(DC, (int)(vRenderPos.x + m_TileSize.x * j)
						, (int)(vRenderPos.y + m_TileSize.y * i)
						, (int)(vRenderPos.x + m_TileSize.x * j + m_TileSize.x)
						, (int)(vRenderPos.y + m_TileSize.y * i + m_TileSize.y));
		}
	}
}

void CTileMap::render_tile()
{
	if (nullptr == m_AtlasTex)
		return;

	Vec2 vRenderPos = GetOwner()->GetRenderPos();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	for (UINT i = 0; i < m_Row; ++i)
	{
		for (UINT j = 0; j < m_Col; ++j)
		{
			// ���� i(��), j(��) �� 1���� �ε����� �ٲپ ������ �Ϸ��� Ÿ���� ������ Vector ���� �����´�.
			int TileIdx = m_Col * i + j;

			// �ش� Ÿ���������� �̹��� �ε����� Ȯ���ϰ�, ��Ʋ�� �ؽ��Ŀ��� �̹��� �ε����� �´� ������ ȭ�鿡 ����Ѵ�.
			UINT TileImgRow = m_vecTileInfo[TileIdx].ImgIdx / m_MaxImgCol;	// ImgIdx�� 1�̰� MaxImgCol�� 10 �̶�� �����ϸ�
			UINT TileImgCol = m_vecTileInfo[TileIdx].ImgIdx % m_MaxImgCol;	// 1�� 1��

			// �ش� Ÿ���� �̹��� �ε����� ��Ʋ�󽺰� ������ Ÿ�� ��, ���� �ʰ��� ���
			assert(!(m_MaxImgRow <= TileImgRow));

			BitBlt(DC, (int)(vRenderPos.x + m_TileSize.x * j)	// �»��
				     , (int)(vRenderPos.y + m_TileSize.y * i)	
					 , m_TileSize.x, m_TileSize.y				// ���ϴ�
					 , m_AtlasTex->GetDC()
					 , TileImgCol * m_TileSize.x				// ���� ImgCol, Row�� 1�̸�
					 , TileImgRow * m_TileSize.y				// 64��ŭ ������ �� ���� ���� ��������� �ϱ� ������
				     , SRCCOPY);							    // TileSize�� ���� ��ġ ���� ���� ��ġ�� ����ش�.
		}
	}
}

void CTileMap::Clicked(Vec2 _MousePos)
{
	// ���콺 ��ǥ�� ���� ���� ���� ��ǥ�� �����Ѵ�.
	_MousePos = CCamera::GetInst()->GetRealPos(_MousePos);

	// Ŭ���� ������ Ÿ�� ������ ��� ������ return �Ѵ�.
	Vec2 vObjPos = GetOwner()->GetPos();

	if (_MousePos.x < vObjPos.x
		|| _MousePos.y < vObjPos.y
		|| vObjPos.x + m_Col * m_TileSize.x < _MousePos.x
		|| vObjPos.y + m_Row * m_TileSize.y < _MousePos.y)
	{
		return;
	}

	// Ÿ�� ��ü�� �̵��� ��츦 �����ؼ� Object�� Position�� ���ش�.
	_MousePos -= vObjPos;

	// ���콺�� Ŭ���� ������ ���� ����� ����Ѵ�.
	int ClickCol = (int)_MousePos.x / m_TileSize.x;
	int ClickRow = (int)_MousePos.y / m_TileSize.y;
	
	// Ŭ���� ������ Ÿ���� 1���� �ε����� �����ؼ� Ÿ�� ���Ϳ��� �ش� ������ �����Ѵ�.
	int TileIdx = m_Col * ClickRow + ClickCol;

	// �ش� Ÿ�� �������� ���� �̹��� �ε����� 1�� ������Ų��.
	m_vecTileInfo[TileIdx].ImgIdx += 1;

	// ���� �̹��� �ε�����, ��Ʋ�󽺿��� �����ϴ� �̹��� ������ �ʰ��ؼ� �����ϰ� �Ǹ�
	// �ٽ� ù��° �̹����� �����ϵ��� �̹��� �ε����� 0 ���� �����Ѵ�.
	if (m_MaxImgCol * m_MaxImgRow <= m_vecTileInfo[TileIdx].ImgIdx)
	{
		m_vecTileInfo[TileIdx].ImgIdx = 0;
	}
}