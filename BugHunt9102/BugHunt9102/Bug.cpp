#include "pch.h"

#include "Bug.h"

Bug::Bug(UINT nIDres, int nRow, int nCol, int nMoveStep, int nHitsRequared, float nDirChangeProb) :
    m_nHitsRequared(nHitsRequared), m_nDirChangeProb(nDirChangeProb), m_iHitsTaken(0), m_iCurrentDir(0)
{
    img_id = nIDres;
    // ����ͼ��
    m_LoadImage(nRow, nCol);

    // Sprite class member
    m_nMoveStep = nMoveStep;

    this->ChangeDirection();
}

BOOL Bug::IsHit(const CPoint& pt)
{
    // �����pt���ھ�����ռ�ľ�����
    if (m_rcSprite.PtInRect(pt))
    {
        // (x,y) Ϊ pt�����bug�����Ͻǵ�����
        int x = pt.x - m_rcSprite.left;
        int y = pt.y - m_rcSprite.top;

        // GetPixel() ����ָ�����������ص�RGB��ɫֵ
        // �����������RGB�����ھ����з�bugͼ�񲿷ֵ�RGBֵ, ˵�����㵽�� bug
        BOOL bHit = (*img_map[img_id]).GetPixel(x, y) != (*img_map[img_id]).GetPixel(0, 0);
        if (bHit)
            ++m_iHitsTaken;

        return bHit;
    }

    return FALSE;
}

void Bug::ChangeDirection()
{
    if (AtLeftEdge() || AtTopEdge() || AtRightEdge() || AtBottomEdge())
        return;
    float randDir = (float)rand();
    if (randDir / RAND_MAX < m_nDirChangeProb)
    {
        m_iCurrentDir = unsigned(rand() % GetPictureCount());
        SetPictureIdx(m_iCurrentDir);
    }
}

///////////////////////////////////////////////
// SlowBug

void SlowBug::Move(int iDevent)
{
    unsigned nDirs = GetPictureCount();

    if (AtTopEdge() || AtBottomEdge())
    {
        m_iCurrentDir = nDirs - m_iCurrentDir;
    }
    else if (AtLeftEdge() || AtRightEdge())
    {
        if (m_iCurrentDir < nDirs / 4)
            m_iCurrentDir = nDirs / 2 - m_iCurrentDir;
        else if (m_iCurrentDir > 3 * nDirs / 4)
            m_iCurrentDir = 3 * nDirs / 2 - m_iCurrentDir;
        else if (m_iCurrentDir > nDirs / 2)
            m_iCurrentDir = 3 * nDirs / 2 - m_iCurrentDir;
        else
            m_iCurrentDir = nDirs / 2 - m_iCurrentDir;
    }

    SetPictureIdx(m_iCurrentDir);

    m_rcSprite.OffsetRect(m_nStepX, m_nStepY);
}

/////////////////////////////////////////////////////
// FastBug
// ���Դ�ǽ������
void FastBug::Move(int iDevent)
{
    //��bug��λ��ƫ��(m_nStepX, m_nStepY), Ҳ������һ��
    m_rcSprite.OffsetRect(m_nStepX, m_nStepY);

    CRect rectClient;
    m_pParentWnd->GetClientRect(rectClient);

    int xOff = rectClient.Width() - m_rcSprite.Width() - 1;
    int yOff = rectClient.Height() - m_rcSprite.Height() - 1;

    if (AtLeftEdge())
    {
        m_rcSprite.OffsetRect(xOff, 0);
    }
    if (AtTopEdge())
    {
        m_rcSprite.OffsetRect(0, yOff);
    }
    if (AtRightEdge())
    {
        m_rcSprite.OffsetRect(-xOff, 0);
    }
    if (AtBottomEdge())
    {
        m_rcSprite.OffsetRect(0, -yOff);
    }
}
