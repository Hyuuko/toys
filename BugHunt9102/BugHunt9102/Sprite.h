#pragma once

#include <atlimage.h>

#include <unordered_map>

#define PI 3.1415926

// �����ܹ���Ӧ���������������������õ�
// iDeventΪNOT_RESPOND����Ӧ
#define NOT_RESPOND -1

// MOVETIGHT �� MOVELEFT ͬʱ����Frog�˶�����ͼƬ��һά����ֵ
#define MOVERIGHT 0
#define MOVELEFT 1
#define MOVEUP 3
#define MOVEDOWN 4

// sprite: ����

// frag �� bug �Ļ���
// һ���������
class Sprite
{
    // �ӿں���
  public:
    Sprite() :
        m_nMoveStep(0),
        m_nStepX(0),
        m_nStepY(0),
        m_nRow(0),
        m_nCol(0),
        m_idxPic(0),
        img_id(0){};

    virtual ~Sprite(); // ����Ϊ virtual���൱��Ҫ
    virtual void Move(int iDevent = NOT_RESPOND) = 0; // ���麯��

    void Draw(CDC* pDC);
    void Erase(CDC* pDC) {}

    // ������
    static void SetParentWnd(CWnd* pParent)
    {
        m_pParentWnd = pParent;
    }

    // ����ʹ�õ�ɫͼ
    static std::unordered_map<UINT, CImage*> img_map;

  protected:
    void m_LoadImage(int nRow, int nCol);
    void SetPictureIdx(unsigned idx);
    int GetPictureIdx() const
    {
        return m_idxPic;
    }

    //�˶�����ͼƬ��һά����ֵ�����ֵ
    int GetPictureCount() const
    {
        return m_nRow * m_nCol;
    }

    // �жϾ�������һ������
    BOOL AtLeftEdge() const;
    BOOL AtRightEdge() const;
    BOOL AtTopEdge() const;
    BOOL AtBottomEdge() const;

  protected:
    CRect m_rcSprite; //����Ĵ�С��λ��, ��LoadImage()ʱ���趨
    int m_nMoveStep;  //�ƶ�һ���ĳ��ȣ���λΪ����
    int m_nStepX;     //x�᷽��ÿһ���ĳ���
    int m_nStepY;     //y�᷽��ÿһ���ĳ���

    int m_idxPic; //���鵱ǰ�˶�����ͼƬ��һά����ֵ��ֵ��Χ[0, m_nRow*m_nCol)

    UINT img_id; //ʹ�õ�ͼƬid

    // ��ͷ�ļ�������
    static CWnd* m_pParentWnd; //���о������ʾ����

    //
  private:
    int m_nRow; //����ͼ�����е�����
    int m_nCol; //����ͼ�����е�����
};


