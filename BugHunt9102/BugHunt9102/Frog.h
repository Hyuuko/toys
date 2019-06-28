#pragma once
#include "Sprite.h"

class Frog : public Sprite
{
  public:
    Frog(UINT nIDres, int nRow, int nCol, int nMoveStep);
    virtual ~Frog();
    CRect GetM_rcSprite()
    {
        return m_rcSprite;
    }

    virtual void Move(int iDevent = NOT_RESPOND);

  protected:
    int GetDir() const
    {
        return m_iCurrentDir;
    }
    void SetDir(int iDir)
    {
        m_iCurrentDir = iDir;
    }

  protected:
    int m_iCurrentDir; // ·½Ïò
};
