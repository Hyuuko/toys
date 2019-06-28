#include "pch.h"

#include "Sprite.h"

// 在实现文件中定义static成员
CWnd* Sprite::m_pParentWnd = 0;
std::unordered_map<UINT, CImage*> Sprite::img_map;

//
Sprite::~Sprite()
{
}

void Sprite::m_LoadImage(int nRow, int nCol)
{
    if (!img_map[img_id])
    {
        img_map[img_id] = new CImage;
        (*img_map[img_id]).LoadFromResource(AfxGetResourceHandle(), img_id);
    }

    //HRESULT ret = m_Bmp.Load(strBitmapFile);
    m_nRow = nRow;
    m_nCol = nCol;

    // 产生一个随机的位置
    // rand()返回 0 与 RAND_MAX 间的随机整数值(包含 0 与 RAND_MAX)
    // RAND_MAX :	#define RAND_MAX 0x7fff   , 即32767
    int x = rand() % 400 + 100;
    int y = rand() % 400 + 100;

    // sprite的宽高
    int cx = (*img_map[img_id]).GetWidth() / nCol;
    int cy = (*img_map[img_id]).GetHeight() / nRow;

    m_rcSprite.SetRect(x, y, x + cx, y + cy);
}

// 判断是否在左边
BOOL Sprite::AtLeftEdge() const
{
    if (m_pParentWnd && m_pParentWnd->IsWindowVisible())
    {
        CRect rectClient;
        m_pParentWnd->GetClientRect(rectClient);

        return m_rcSprite.left <= rectClient.left;
    }

    return FALSE;
}

BOOL Sprite::AtRightEdge() const
{
    if (m_pParentWnd && m_pParentWnd->IsWindowVisible())
    {
        CRect rectClient;
        m_pParentWnd->GetClientRect(rectClient);

        return m_rcSprite.right >= rectClient.right;
    }

    return FALSE;
}

BOOL Sprite::AtTopEdge() const
{
    if (m_pParentWnd && m_pParentWnd->IsWindowVisible())
    {
        CRect rectClient;
        m_pParentWnd->GetClientRect(rectClient);

        return m_rcSprite.top <= rectClient.top;
    }

    return FALSE;
}
BOOL Sprite::AtBottomEdge() const
{
    if (m_pParentWnd && m_pParentWnd->IsWindowVisible())
    {
        CRect rectClient;
        m_pParentWnd->GetClientRect(rectClient);

        return m_rcSprite.bottom >= rectClient.bottom;
    }

    return FALSE;
}

// 绘制
void Sprite::Draw(CDC* pDC)
{
    ASSERT(pDC);
    if (!pDC)
        return;

    int cx = m_rcSprite.Width();
    int cy = m_rcSprite.Height();

    int iRow = m_idxPic / m_nCol;
    int iCol = m_idxPic % m_nCol;
    int x    = iCol * cx;
    int y    = iRow * cy;

    COLORREF clrBknd = (*img_map[img_id]).GetPixel(0, 0);
    HDC hDC          = pDC->GetSafeHdc();

    // 绘制透明位图
    (*img_map[img_id]).TransparentBlt(hDC, m_rcSprite.left, m_rcSprite.top, cx, cy, x, y, cx, cy, clrBknd);
}

//根据m_iCurrentDir值来判断是哪个图
//据观察,发现[1,1] -> ... -> [1,18] -> [2,1] -> ... -> [2,18] -> ...... -> [4,18]过程中,
//bug的头部与x轴的夹角为 0 -> 360
void Sprite::SetPictureIdx(unsigned idx)
{
    //m_idxPic用来确定用的是哪一张图
    m_idxPic = idx;

    double deg = 0.0;
    //deg为bug的头部与x轴的夹角
    deg = 360.0 * double(idx) / GetPictureCount();

    //强制类型转换为int
    m_nStepX = int(m_nMoveStep * cos(deg / 180.0 * PI));
    m_nStepY = -int(m_nMoveStep * sin(deg / 180.0 * PI));
}
