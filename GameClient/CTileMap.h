#pragma once
#include "CComponent.h"

struct tTileInfo
{
    int ImgIdx;

    tTileInfo()
        : ImgIdx(0)
    {}

}; // Ÿ���� �ε����� ���� ����ü

class CTexture;

class CTileMap :
    public CComponent
{
private:
    UINT              m_Row;                     // ��
    UINT              m_Col;                     // ��
    Vec2              m_TileSize;                // Ÿ�� ������
                      
    CTexture*         m_AtlasTex;           // Ÿ���� ����ϴ� ��Ʋ�� �ؽ���
    UINT              m_MaxImgRow;          // ��Ʋ�� �ؽ��İ� �����ϰ� �ִ� Ÿ�� �̹��� ����(��) ����
    UINT              m_MaxImgCol;          // ��Ʋ�� �ؽ��İ� �����ϰ� �ִ� Ÿ�� �̹��� ����(��) ����

    vector<tTileInfo> m_vecTileInfo;
    
public:
    void SetRow(UINT _Row);
    void SetCol(UINT _Col);
    void SetRowCol(UINT _Row, UINT _Col);
    
    UINT GetRow() { return m_Row; }
    UINT GetCol() { return m_Col; }
    
    void SetAtlasTex(CTexture* _Atlas);
    CTexture* GetAtlasTex() { return m_AtlasTex; }

    void Clicked(Vec2 _MousePos);

public:
    virtual void finaltick() override;
    void render();

private:
    void render_grid();
    void render_tile();

public:
    CLONE(CTileMap)
    CTileMap();
    //CTileMap(const CTileMap& _Other);
    ~CTileMap();
};

