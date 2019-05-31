
// BugHunt9102Doc.h: CBugHunt9102Doc 类的接口
//

#pragma once

#include "Bug.h"
#include "Frog.h"
#include <vector>

class CBugHunt9102Doc : public CDocument {
  protected: // 仅从序列化创建
    CBugHunt9102Doc() noexcept;
    DECLARE_DYNCREATE(CBugHunt9102Doc)

    //返回指向Bug的指针容器
  public:
    const std::vector<Bug*>& GetBugList() const {
        return m_listBug;
    }
    std::vector<Bug*>& GetBugList() {
        return m_listBug;
    }

    Frog*& GetFrog() {
        return pFrog;
    }

    void AddBug(UINT nIDres, int nRow, int nCol,
                int nMoveStep, int nHitsRequared, float nDirChangeProb);

    void BugEaten();

    // 特性
  public:
    // 操作
  public:
    // 重写
  public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

    // 实现
  public:
    virtual ~CBugHunt9102Doc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    // Bug 和 Frog
  protected:
    std::vector<Bug*> m_listBug;
    Frog* pFrog;

    // 生成的消息映射函数
  protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // 用于为搜索处理程序设置搜索内容的 Helper 函数
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
