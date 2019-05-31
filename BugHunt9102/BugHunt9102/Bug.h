#pragma once
#include "Sprite.h"

class Bug : public Sprite {
  public:
    explicit Bug(UINT nIDres, int nRow, int nCol,
                 int nMoveStep, int nHitsRequared, float nDirChangeProb);
    virtual ~Bug();

    BOOL IsHit(const CPoint& pt);
    BOOL IsDying() const {
        return m_iHitsTaken >= m_nHitsRequared;
    }
    void Kill(CDC* pDC) {
        ;
    }

    void ChangeDirection();
    virtual void Move() = 0; // 纯虚函数

  protected:
    unsigned GetCurrDir() const {
        return m_iCurrentDir;
    }
    void SetCurrDir(unsigned iDirection) {
        m_iCurrentDir = iDirection;
    }
    float GetDirChangeProb() const {
        return m_nDirChangeProb;
    }

  protected:
    int m_nHitsRequared;    // the requared hit number to kill the bug
    int m_iHitsTaken;       // the hit number that bug has be taken
    float m_nDirChangeProb; // 	SetTimer(ID_TIMER_BUGCHANGEDIR, 1000, NULL); 每隔1000ms内改变方向的可能性
    unsigned m_iCurrentDir; // the current moving direction
};

class FastBug : public Bug {
  public:
    explicit FastBug(UINT nIDres, int nRow, int nCol,
                     int nMoveStep, int nHitsRequared, float nDirChangeProb) :
        Bug(nIDres, nRow, nCol, nMoveStep, nHitsRequared, nDirChangeProb) {}

    ~FastBug() {}

    virtual void Move();
};

class SlowBug : public Bug {
  public:
    explicit SlowBug(UINT nIDres, int nRow, int nCol,
                     int nMoveStep, int nHitsRequared, float nDirChangeProb) :
        Bug(nIDres, nRow, nCol, nMoveStep, nHitsRequared, nDirChangeProb) {}

    ~SlowBug() {}

    virtual void Move();
};