#include "pch.h"

#include "Bug.h"

Bug::Bug(UINT nIDres, int nRow, int nCol,
         int nMoveStep, int nHitsRequared, float nDirChangeProb) :
    m_nHitsRequared(nHitsRequared),
    m_nDirChangeProb(nDirChangeProb),
    m_iHitsTaken(0), m_iCurrentDir(0) {
    LoadImage(nIDres, nRow, nCol);

    // Sprite class member
    m_nMoveStep = nMoveStep;
}

Bug::~Bug() {}

BOOL Bug::IsHit(const CPoint& pt) {

    // 如果该pt点在精灵所占的矩形里
    if (m_rcSprite.PtInRect(pt)) {

        // (x,y) 为 pt相对于bug的左上角的坐标
        int x = pt.x - m_rcSprite.left;
        int y = pt.y - m_rcSprite.top;

        // GetPixel() 检索指定坐标点的像素的RGB颜色值
        // 如果相对坐标的RGB不等于矩形中非bug图像部分的RGB值, 说明鼠标点到了 bug
        BOOL bHit = m_Bmp.GetPixel(x, y) != m_Bmp.GetPixel(0, 0);
        if (bHit)
            ++m_iHitsTaken;

        return bHit;
    }

    return FALSE;
}

void Bug::ChangeDirection() {
    if (AtLeftEdge() || AtTopEdge() || AtRightEdge() || AtBottomEdge())
        return;
    float randDir = (float)rand();
    if (randDir / RAND_MAX < m_nDirChangeProb) {
        m_iCurrentDir = unsigned(rand() % GetPictureCount());
        SetPictureIdx(m_iCurrentDir);
    }
}

///////////////////////////////////////////////
// SlowBug

void SlowBug::Move() {

    unsigned nDirs = GetPictureCount();

#if 0
	if (AtLeftEdge() || AtTopEdge() || AtRightEdge() || AtBottomEdge()) {
		m_iCurrentDir += nDirs / 2;
		if (m_iCurrentDir > nDirs)
			m_iCurrentDir -= nDirs;
	}
#endif

#if 1
    if (AtTopEdge() || AtBottomEdge()) {
        m_iCurrentDir = nDirs - m_iCurrentDir;
    } else if (AtLeftEdge() || AtRightEdge()) {
        if (m_iCurrentDir < nDirs / 4)
            m_iCurrentDir = nDirs / 2 - m_iCurrentDir;
        else if (m_iCurrentDir > 3 * nDirs / 4)
            m_iCurrentDir = 3 * nDirs / 2 - m_iCurrentDir;
        else if (m_iCurrentDir > nDirs / 2)
            m_iCurrentDir = 3 * nDirs / 2 - m_iCurrentDir;
        else
            m_iCurrentDir = nDirs / 2 - m_iCurrentDir;
    }
#endif

    SetPictureIdx(m_iCurrentDir);

    m_rcSprite.OffsetRect(m_nStepX, m_nStepY);
}

/////////////////////////////////////////////////////
// FastBug
// 可以穿墙而过的
void FastBug::Move() {
    //让bug的位置偏移(m_nStepX, m_nStepY), 也就是走一步
    m_rcSprite.OffsetRect(m_nStepX, m_nStepY);

    CRect rectClient;
    m_pParentWnd->GetClientRect(rectClient);

    int xOff = rectClient.Width() - m_rcSprite.Width() - 1;
    int yOff = rectClient.Height() - m_rcSprite.Height() - 1;

    if (AtLeftEdge()) {
        m_rcSprite.OffsetRect(xOff, 0);
    }
    if (AtTopEdge()) {
        m_rcSprite.OffsetRect(0, yOff);
    }
    if (AtRightEdge()) {
        m_rcSprite.OffsetRect(-xOff, 0);
    }
    if (AtBottomEdge()) {
        m_rcSprite.OffsetRect(0, -yOff);
    }

    // SetPictureIdx(m_iCurrentDir);
}
