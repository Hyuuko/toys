#pragma once

#include <atlimage.h>

#include <unordered_map>

#define PI 3.1415926

// 对于能够响应方向键的派生类对象是有用的
// iDevent为NOT_RESPOND则不响应
#define NOT_RESPOND -1

// MOVETIGHT 和 MOVELEFT 同时还是Frog运动方向图片的一维索引值
#define MOVERIGHT 0
#define MOVELEFT 1
#define MOVEUP 3
#define MOVEDOWN 4

// sprite: 精灵

// frag 和 bug 的基类
// 一个抽象基类
class Sprite
{
    // 接口函数
  public:
    Sprite() :
        m_nMoveStep(0),
        m_nStepX(0),
        m_nStepY(0),
        m_nRow(0),
        m_nCol(0),
        m_idxPic(0),
        img_id(0){};

    virtual ~Sprite(); // 声明为 virtual，相当重要
    virtual void Move(int iDevent = NOT_RESPOND) = 0; // 纯虚函数

    void Draw(CDC* pDC);
    void Erase(CDC* pDC) {}

    // 父窗口
    static void SetParentWnd(CWnd* pParent)
    {
        m_pParentWnd = pParent;
    }

    // 所有使用的色图
    static std::unordered_map<UINT, CImage*> img_map;

  protected:
    void m_LoadImage(int nRow, int nCol);
    void SetPictureIdx(unsigned idx);
    int GetPictureIdx() const
    {
        return m_idxPic;
    }

    //运动方向图片的一维索引值的最大值
    int GetPictureCount() const
    {
        return m_nRow * m_nCol;
    }

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

    UINT img_id; //使用的图片id

    // 在头文件中声明
    static CWnd* m_pParentWnd; //所有精灵的显示窗口

    //
  private:
    int m_nRow; //精灵图像阵列的行数
    int m_nCol; //精灵图像阵列的列数
};


