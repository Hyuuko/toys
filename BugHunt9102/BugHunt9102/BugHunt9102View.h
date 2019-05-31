// BugHunt9102View.h: CBugHunt9102View 类的接口
//

#pragma once

class CBugHunt9102View : public CView {
  protected: // 仅从序列化创建
    CBugHunt9102View() noexcept;
    DECLARE_DYNCREATE(CBugHunt9102View)

    // 特性
  public:
    CBugHunt9102Doc* GetDocument() const;

    // 操作
  public:
    // 重写
  public:
    virtual void OnDraw(CDC* pDC); // 重写以绘制该视图
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  protected:
    // 实现
  public:
    virtual ~CBugHunt9102View();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

  protected:
    //背景图片
    CImage m_bmpBackgrnd;

    // 生成的消息映射函数
  protected:
    DECLARE_MESSAGE_MAP()
  public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG // BugHunt9102View.cpp 中的调试版本
inline CBugHunt9102Doc* CBugHunt9102View::GetDocument() const {
    return reinterpret_cast<CBugHunt9102Doc*>(m_pDocument);
}
#endif
