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

	// vector를 clear 시켜주고 1차원 이지만 행열 개념을 만들어준다.
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
		// 내 최대 행 열 계산
		// TileSize를 64 x 64로 맞춰놨기 때문에 해당 Tile의 Atlas 가로 세로 위치에 64를 나누어주면 최대 행열 개수가 나오게된다.
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
			// 사각형 그리는데 좌상단은 내 현재 Render Position x에 Tile의 사이즈를 j(열)에 곱해주고 더해준다.
			// 좌상단 y Position은 행(i)을 곱해준다.
			// 우하단은 Render Position에 Tile의 사이즈를 열에 곱해서 더해준 다음 타일의 사이즈를 한번 더 더해준다.
			// 우하단 y Position은 행을 곱해주고 Tile의 사이즈를 더해준다.
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
			// 현재 i(행), j(열) 을 1차원 인덱스로 바꾸어서 렌더링 하려는 타일의 정보를 Vector 에서 꺼내온다.
			int TileIdx = m_Col * i + j;

			// 해당 타일정보에서 이미지 인덱스를 확인하고, 아틀라스 텍스쳐에서 이미지 인덱스에 맞는 부위를 화면에 출력한다.
			UINT TileImgRow = m_vecTileInfo[TileIdx].ImgIdx / m_MaxImgCol;	// ImgIdx가 1이고 MaxImgCol이 10 이라고 가정하면
			UINT TileImgCol = m_vecTileInfo[TileIdx].ImgIdx % m_MaxImgCol;	// 1행 1열

			// 해당 타일의 이미지 인덱스가 아틀라스가 보유한 타일 행, 열을 초과한 경우
			assert(!(m_MaxImgRow <= TileImgRow));

			BitBlt(DC, (int)(vRenderPos.x + m_TileSize.x * j)	// 좌상단
				     , (int)(vRenderPos.y + m_TileSize.y * i)	
					 , m_TileSize.x, m_TileSize.y				// 우하단
					 , m_AtlasTex->GetDC()
					 , TileImgCol * m_TileSize.x				// 만약 ImgCol, Row가 1이면
					 , TileImgRow * m_TileSize.y				// 64만큼 떨어진 행 열로 가서 복사해줘야 하기 때문에
				     , SRCCOPY);							    // TileSize를 곱한 위치 값을 복사 위치로 잡아준다.
		}
	}
}

void CTileMap::Clicked(Vec2 _MousePos)
{
	// 마우스 좌표를 실제 게임 공간 좌표로 변경한다.
	_MousePos = CCamera::GetInst()->GetRealPos(_MousePos);

	// 클릭한 지점이 타일 영역을 벗어나 있으면 return 한다.
	Vec2 vObjPos = GetOwner()->GetPos();

	if (_MousePos.x < vObjPos.x
		|| _MousePos.y < vObjPos.y
		|| vObjPos.x + m_Col * m_TileSize.x < _MousePos.x
		|| vObjPos.y + m_Row * m_TileSize.y < _MousePos.y)
	{
		return;
	}

	// 타일 전체가 이동된 경우를 생각해서 Object의 Position을 빼준다.
	_MousePos -= vObjPos;

	// 마우스가 클릭한 지점이 몇행 몇열인지 계산한다.
	int ClickCol = (int)_MousePos.x / m_TileSize.x;
	int ClickRow = (int)_MousePos.y / m_TileSize.y;
	
	// 클릭한 지점의 타일을 1차원 인덱스로 변경해서 타일 벡터에서 해당 정보에 접근한다.
	int TileIdx = m_Col * ClickRow + ClickCol;

	// 해당 타일 정보에서 참조 이미지 인덱스를 1개 증가시킨다.
	m_vecTileInfo[TileIdx].ImgIdx += 1;

	// 만약 이미지 인덱스가, 아틀라스에서 제공하는 이미지 개수를 초과해서 참조하게 되면
	// 다시 첫번째 이미지를 참조하도록 이미지 인덱스를 0 으로 설정한다.
	if (m_MaxImgCol * m_MaxImgRow <= m_vecTileInfo[TileIdx].ImgIdx)
	{
		m_vecTileInfo[TileIdx].ImgIdx = 0;
	}
}