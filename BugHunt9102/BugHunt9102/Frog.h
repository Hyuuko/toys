#pragma once
#include "Sprite.h"

// MOVETIGHT 和 MOVELEFT 同时还是Frog运动方向图片的一维索引值
#define MOVERIGHT 0
#define MOVELEFT 1
#define MOVEUP 3
#define MOVEDOWN 4

class Frog : public Sprite {
  public:
    explicit Frog(UINT nIDres, int nRow, int nCol, int nMoveStep);
    virtual ~Frog();
    CRect GetM_rcSprite() {
        return m_rcSprite;
    }

    void FrogMove(int iDevent);
    virtual void Move() {
        ;
    }

  protected:
    int GetDir() const {
        return m_iCurrentDir;
    }
    void SetDir(int iDir) {
        m_iCurrentDir = iDir;
    }

  protected:
    int m_iCurrentDir; // 方向
};
