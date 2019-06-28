#include "pch.h"

#include "Sprite.h"

// ��ʵ���ļ��ж���static��Ա
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

    // ����һ�������λ��
    // rand()���� 0 �� RAND_MAX ����������ֵ(���� 0 �� RAND_MAX)
    // RAND_MAX :	#define RAND_MAX 0x7fff   , ��32767
    int x = rand() % 400 + 100;
    int y = rand() % 400 + 100;

    // sprite�Ŀ��
    int cx = (*img_map[img_id]).GetWidth() / nCol;
    int cy = (*img_map[img_id]).GetHeight() / nRow;

    m_rcSprite.SetRect(x, y, x + cx, y + cy);
}

// �ж��Ƿ������
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

// ����
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

    // ����͸��λͼ
    (*img_map[img_id]).TransparentBlt(hDC, m_rcSprite.left, m_rcSprite.top, cx, cy, x, y, cx, cy, clrBknd);
}

//����m_iCurrentDirֵ���ж����ĸ�ͼ
//�ݹ۲�,����[1,1] -> ... -> [1,18] -> [2,1] -> ... -> [2,18] -> ...... -> [4,18]������,
//bug��ͷ����x��ļн�Ϊ 0 -> 360
void Sprite::SetPictureIdx(unsigned idx)
{
    //m_idxPic����ȷ���õ�����һ��ͼ
    m_idxPic = idx;

    double deg = 0.0;
    //degΪbug��ͷ����x��ļн�
    deg = 360.0 * double(idx) / GetPictureCount();

    //ǿ������ת��Ϊint
    m_nStepX = int(m_nMoveStep * cos(deg / 180.0 * PI));
    m_nStepY = -int(m_nMoveStep * sin(deg / 180.0 * PI));
}
