#include "pch.h"

#include "Frog.h"

Frog::Frog(UINT nIDres, int nRow, int nCol, int nMoveStep) :
    m_iCurrentDir(0)
{
    img_id = nIDres;
    m_LoadImage(nRow, nCol);

    m_nMoveStep = nMoveStep;
}
Frog::~Frog()
{
}

void Frog::Move(int iDevent)
{
    switch (iDevent)
    {
    case MOVEUP:
        // ��������߽�
        if (!AtTopEdge())
            m_rcSprite.OffsetRect(0, -m_nMoveStep);
        break;
    case MOVEDOWN:
        if (!AtBottomEdge())
            m_rcSprite.OffsetRect(0, m_nMoveStep);
        break;
    case MOVELEFT:
        if (!AtLeftEdge())
        {
            m_idxPic = MOVELEFT; // ����תʱ���ܵ�ͼƬҪ��
            m_rcSprite.OffsetRect(-m_nMoveStep, 0);
        }
        break;
    case MOVERIGHT:
        if (!AtRightEdge())
        {
            m_idxPic = MOVERIGHT;
            m_rcSprite.OffsetRect(m_nMoveStep, 0);
        }
        break;
    default:
        // no thing to do
        break;
    }
}
