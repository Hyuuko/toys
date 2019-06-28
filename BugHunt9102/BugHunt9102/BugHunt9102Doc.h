// BugHunt9102Doc.h: CBugHunt9102Doc 类的接口
//

#pragma once

#include "Bug.h"
#include "Frog.h"

#include <list>

class CBugHunt9102Doc : public CDocument
{
  protected: // 仅从序列化创建
    CBugHunt9102Doc() noexcept;
    DECLARE_DYNCREATE(CBugHunt9102Doc)

  public:
	// const 对象只能调用 const 成员函数
    const std::list<Bug*>& GetBugList() const
    {
        return m_listBug;
    }
	// 非cnost 对象可以访问所有函数
    std::list<Bug*>& GetBugList()
    {
        return m_listBug;
    }

    Frog*& GetFrog()
    {
        return pFrog;
    }

    void AddBlueBug();
    void AddRedBug();

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

    // Bug 和 Frog 数据成员
  private:
    std::list<Bug*> m_listBug;
    Frog* pFrog;

    // 生成的消息映射函数
  protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // 用于为搜索处理程序设置搜索内容的 Helper 函数
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
