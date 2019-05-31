#ifndef _LYM_SPRITE_INC
#define _LYM_SPRITE_INC

#pragma once
#include <atlimage.h>

#define PI 3.1415926

// sprite: 精灵

// frag 和 bug 的基类
// 抽象基类
class Sprite {

    // 接口函数
  public:
    Sprite();
    virtual ~Sprite();

    void Draw(CDC *pDC);
    void Erase(CDC *pDC) {}

    virtual void Move() = 0; // 纯虚函数

    // 父窗口
    static void SetParentWnd(CWnd *pParent) {
        m_pParentWnd = pParent;
    }

  protected:
    void LoadImage(UINT nIDres, int nRow, int nCol);
    void SetPictureIdx(unsigned idx);
    int GetPictureIdx() const {
        return m_idxPic;
    }

    //运动方向图片的一维索引值的最大值
    int GetPictureCount() const {
        return m_nRow * m_nCol;
    }
    CSize GetPictureDimension() const;

    // 判断精灵在哪一条边上
    BOOL AtLeftEdge() const;
    BOOL AtRightEdge() const;
    BOOL AtTopEdge() const;
    BOOL AtBottomEdge() const;

  protected:
    CRect m_rcSprite; //精灵的大小和位置, 在LoadImage()时被设定
    int m_nMoveStep;  //移动一步的长度，单位为像素
    int m_nStepX;     //x轴方向每一步的长度
    int m_nStepY;     //y轴方向每一步的长度

    int m_idxPic; //精灵当前运动方向图片的一维索引值，值范围[0, m_nRow*m_nCol)

    //
    static CWnd *m_pParentWnd; //所有精灵的显示窗口
    CImage m_Bmp;              //精灵图像

  private:
    int m_nRow; //精灵图像阵列的行数
    int m_nCol; //精灵图像阵列的列数
};

#endif //_LYM_SPRITE_INC