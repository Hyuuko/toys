#ifndef _LYM_SPRITE_INC
#define _LYM_SPRITE_INC

#pragma once
#include <atlimage.h>

#define PI 3.1415926

// sprite: ����

// frag �� bug �Ļ���
// �������
class Sprite {

    // �ӿں���
  public:
    Sprite();
    virtual ~Sprite();

    void Draw(CDC *pDC);
    void Erase(CDC *pDC) {}

    virtual void Move() = 0; // ���麯��

    // ������
    static void SetParentWnd(CWnd *pParent) {
        m_pParentWnd = pParent;
    }

  protected:
    void LoadImage(UINT nIDres, int nRow, int nCol);
    void SetPictureIdx(unsigned idx);
    int GetPictureIdx() const {
        return m_idxPic;
    }

    //�˶�����ͼƬ��һά����ֵ�����ֵ
    int GetPictureCount() const {
        return m_nRow * m_nCol;
    }
    CSize GetPictureDimension() const;

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

    //
    static CWnd *m_pParentWnd; //���о������ʾ����
    CImage m_Bmp;              //����ͼ��

  private:
    int m_nRow; //����ͼ�����е�����
    int m_nCol; //����ͼ�����е�����
};

#endif //_LYM_SPRITE_INC