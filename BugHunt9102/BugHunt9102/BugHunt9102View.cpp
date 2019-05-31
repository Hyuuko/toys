// BugHunt9102View.cpp: CBugHunt9102View 类的实现
//
#include "pch.h"

#include "framework.h"
#include "resource.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#    include "BugHunt9102.h"
#endif

#include "BugHunt9102Doc.h"
#include "BugHunt9102View.h"

#ifdef _DEBUG
#    define new DEBUG_NEW
#endif

#define ID_TIMER_BUGMOVE 100
#define ID_TIMER_BUGCHANGEDIR 200

// CBugHunt9102View

IMPLEMENT_DYNCREATE(CBugHunt9102View, CView)

BEGIN_MESSAGE_MAP(CBugHunt9102View, CView)
ON_WM_TIMER()
ON_WM_CREATE()
ON_WM_ERASEBKGND()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CBugHunt9102View 构造/析构

CBugHunt9102View::CBugHunt9102View() noexcept {
    // TODO: 在此处添加构造代码
    m_bmpBackgrnd.LoadFromResource(AfxGetResourceHandle(), IDB_BKG);

    Sprite::SetParentWnd(this);
}

CBugHunt9102View::~CBugHunt9102View() {
}

BOOL CBugHunt9102View::PreCreateWindow(CREATESTRUCT& cs) {
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return CView::PreCreateWindow(cs);
}

// CBugHunt9102View 绘图

void CBugHunt9102View::OnDraw(CDC* pDC) {
    CBugHunt9102Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: 在此处为本机数据添加绘制代码
    CRect rectClient;
    GetClientRect(rectClient);

    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap bmp;
    bmp.CreateCompatibleBitmap(pDC, rectClient.Width(), rectClient.Height());
    memDC.SelectObject(bmp);
    memDC.FillSolidRect(rectClient, RGB(255, 255, 255));

    int w = m_bmpBackgrnd.GetWidth();
    int h = m_bmpBackgrnd.GetHeight();
    int x = (rectClient.Width() - w) / 2;
    int y = (rectClient.Height() - h) / 2;

    // 画背景, (x,y)为图左上角的位置
    m_bmpBackgrnd.Draw(memDC.GetSafeHdc(), x, y);

    // 检查虫子有没有碰到被吃掉
    pDoc->BugEaten();

    // 画虫子
    for (auto p : pDoc->GetBugList()) {
        if (p)
            p->Draw(&memDC);
    }
    //画青蛙
    pDoc->GetFrog()->Draw(&memDC);

    pDC->BitBlt(0, 0, rectClient.Width(), rectClient.Height(), &memDC, 0, 0, SRCCOPY);
}

// CBugHunt9102View 诊断

#ifdef _DEBUG
void CBugHunt9102View::AssertValid() const {
    CView::AssertValid();
}

void CBugHunt9102View::Dump(CDumpContext& dc) const {
    CView::Dump(dc);
}

CBugHunt9102Doc* CBugHunt9102View::GetDocument() const // 非调试版本是内联的
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBugHunt9102Doc)));
    return (CBugHunt9102Doc*)m_pDocument;
}
#endif //_DEBUG

// CBugHunt9102View 消息处理程序

int CBugHunt9102View::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码

    // 定时器标号，定时时间（ms）。启动定时器 ID_TIMER_XXXX，每隔xxms刷新一次
    //每隔 10ms bug走一步
    SetTimer(ID_TIMER_BUGMOVE, 10, NULL);
    //每隔 1000ms 考虑一下是否改变方向(概率为m_nDirChangeProb)
    SetTimer(ID_TIMER_BUGCHANGEDIR, 1000, NULL);

    return 0;
}

// 用来决定是否使CBugHunt9102View::OnTimer函数中的程序生效, 从而实现暂停
bool isPause = false;
void CBugHunt9102View::OnTimer(UINT_PTR nIDEvent) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    // 如果处于暂停状态，退出该函数
    if (isPause)
        return;

    CBugHunt9102Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    switch (nIDEvent) {

        // 移动
    case ID_TIMER_BUGMOVE: // ID_TIMER_BUGMOVE 见第二十行
        for (auto p : pDoc->GetBugList())
            if (p)
                p->Move();
        break;

        // 改变方向
    case ID_TIMER_BUGCHANGEDIR:
        for (auto p : pDoc->GetBugList())
            if (p)
                p->ChangeDirection();
        break;

    default:
        break;
    }

    Invalidate(); // 重绘窗口

    CView::OnTimer(nIDEvent);
}

BOOL CBugHunt9102View::OnEraseBkgnd(CDC* pDC) {
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    //这里改动了, 青蛙背景不闪了
    return true;
    //return CView::OnEraseBkgnd(pDC);
}

void CBugHunt9102View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    CBugHunt9102Doc* pDoc = GetDocument();
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    switch (nChar) {
        // 🈲术
    case VK_RETURN:
        for (auto& p : pDoc->GetBugList()) {
            if (p) {
                delete p;
                p = NULL;
            }
        }

        // 灭霸指令
    case VK_F1:
        for (auto& p : pDoc->GetBugList()) {
            int i = rand() * 2 - RAND_MAX;
            if (p && i > 0) {
                delete p;
                p = NULL;
            }
        }
        break;
    case VK_UP:
        pDoc->GetFrog()->FrogMove(MOVEUP);
        break;
    case VK_DOWN:
        pDoc->GetFrog()->FrogMove(MOVEDOWN);
        break;
    case VK_LEFT:
        pDoc->GetFrog()->FrogMove(MOVELEFT);
        break;
    case VK_RIGHT:
        pDoc->GetFrog()->FrogMove(MOVERIGHT);
        break;
    case VK_SPACE:
        isPause = isPause ? false : true;
        break;
    case 65:
        // 65为A的Ascall码
        pDoc->AddBug(IDB_BLUEBUG, 4, 18, 3, 1, 0.5);
        break;
    default:
        // Nothing to do
        break;
    }

    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
