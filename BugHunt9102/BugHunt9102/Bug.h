#pragma once
#include "Sprite.h"

// 没有对抽象基类的虚函数重新定义，Bug也是抽象基类

class Bug : public Sprite
{
  public:
    Bug(UINT nIDres, int nRow, int nCol, int nMoveStep, int nHitsRequared, float nDirChangeProb);

    BOOL IsHit(const CPoint& pt);
    BOOL IsDying() const
    {
        return m_iHitsTaken >= m_nHitsRequared;
    }
    void Kill(CDC* pDC) {}

    // 修改

    void ChangeDirection();
    void SetCurrDir(unsigned iDirection)
    {
        m_iCurrentDir = iDirection;
    }

    // 访问
  protected:
    unsigned GetCurrDir() const
    {
        return m_iCurrentDir;
    }

    float GetDirChangeProb() const
    {
        return m_nDirChangeProb;
    }

    // 数据成员
  protected:
    int m_nHitsRequared;    // the requared hit number to kill the bug
    int m_iHitsTaken;       // the hit number that bug has be taken
    float m_nDirChangeProb; // 	SetTimer(ID_TIMER_BUGCHANGEDIR, 1000, NULL); 每隔1000ms内改变方向的可能性
    unsigned m_iCurrentDir; // the current moving direction
};

class FastBug : public Bug
{
  public:
    FastBug(UINT nIDres, int nRow, int nCol, int nMoveStep, int nHitsRequared, float nDirChangeProb) :
        Bug(nIDres, nRow, nCol, nMoveStep, nHitsRequared, nDirChangeProb) {}

    ~FastBug() {}

    virtual void Move(int iDevent = NOT_RESPOND);
};

class SlowBug : public Bug
{
  public:
    SlowBug(UINT nIDres, int nRow, int nCol, int nMoveStep, int nHitsRequared, float nDirChangeProb) :
        Bug(nIDres, nRow, nCol, nMoveStep, nHitsRequared, nDirChangeProb) {}

    ~SlowBug() {}

    virtual void Move(int iDevent = NOT_RESPOND);
};