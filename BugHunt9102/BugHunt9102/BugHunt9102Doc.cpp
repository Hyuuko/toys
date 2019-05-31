// BugHunt9102Doc.cpp: CBugHunt9102Doc 类的实现
//
#include "pch.h"

#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#    include "BugHunt9102.h"
#endif

#include "BugHunt9102Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#    define new DEBUG_NEW
#endif

// CBugHunt9102Doc

IMPLEMENT_DYNCREATE(CBugHunt9102Doc, CDocument)

BEGIN_MESSAGE_MAP(CBugHunt9102Doc, CDocument)
END_MESSAGE_MAP()

// CBugHunt9102Doc 构造/析构

CBugHunt9102Doc::CBugHunt9102Doc() noexcept {
    // TODO: 在此添加一次性构造代码
    // 5个FastBug
    // nSpeed没用
    for (int i = 0; i != 5; ++i) {
        Bug* pBug =
            new FastBug(IDB_BLUEBUG, 4, 18, 3, 1, 0.5);
        pBug->ChangeDirection();
        m_listBug.push_back(pBug);
    }
    // 5个SlowBug
    for (int i = 0; i != 5; ++i) {
        Bug* pBug =
            new SlowBug(IDB_REDBUG, 4, 18, 5, 1, 0.5);
        pBug->ChangeDirection();
        m_listBug.push_back(pBug);
    }

    pFrog = new Frog(IDB_FROG, 1, 2, 20);
}

CBugHunt9102Doc::~CBugHunt9102Doc() {
    for (auto p : GetBugList())
        if (p) {
            delete p;
        }
    if (pFrog) {
        delete pFrog;
    }
}

BOOL CBugHunt9102Doc::OnNewDocument() {
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: 在此添加重新初始化代码
    // (SDI 文档将重用该文档)

    return TRUE;
}

// CBugHunt9102Doc 序列化

void CBugHunt9102Doc::Serialize(CArchive& ar) {
    if (ar.IsStoring()) {
        // TODO:  在此添加存储代码
    } else {
        // TODO:  在此添加加载代码
    }
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CBugHunt9102Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
    // 修改此代码以绘制文档数据
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CBugHunt9102Doc::InitializeSearchContent() {
    CString strSearchContent;
    // 从文档数据设置搜索内容。
    // 内容部分应由“;”分隔

    // 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
    SetSearchContent(strSearchContent);
}

void CBugHunt9102Doc::SetSearchContent(const CString& value) {
    if (value.IsEmpty()) {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    } else {
        CMFCFilterChunkValueImpl* pChunk = nullptr;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != nullptr) {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif // SHARED_HANDLERS

// CBugHunt9102Doc 诊断

#ifdef _DEBUG
void CBugHunt9102Doc::AssertValid() const {
    CDocument::AssertValid();
}

void CBugHunt9102Doc::Dump(CDumpContext& dc) const {
    CDocument::Dump(dc);
}
#endif //_DEBUG

// CBugHunt9102Doc 命令

void CBugHunt9102Doc::BugEaten() {

    CPoint point1(pFrog->GetM_rcSprite().left, pFrog->GetM_rcSprite().top);
    CPoint point2(pFrog->GetM_rcSprite().left, pFrog->GetM_rcSprite().bottom);
    CPoint point3(pFrog->GetM_rcSprite().right, pFrog->GetM_rcSprite().top);
    CPoint point4(pFrog->GetM_rcSprite().right, pFrog->GetM_rcSprite().bottom);

    // bug死亡时, 连同指向bug对象的buglist成员也一同删去
    for (auto it = m_listBug.begin(); it != m_listBug.end();)
        if (*it && ((*it)->IsHit(point1) || (*it)->IsHit(point2) || (*it)->IsHit(point3) || (*it)->IsHit(point4))) {
            delete (*it);
            it = m_listBug.erase(it);
        } else
            it++;
}

// 加一个FastBug
void CBugHunt9102Doc::AddBug(UINT nIDres, int nRow, int nCol,
                             int nMoveStep, int nHitsRequared, float nDirChangeProb) {
    Bug* pBug =
        new FastBug(nIDres, nRow, nCol, nMoveStep, nHitsRequared, nDirChangeProb);
    pBug->ChangeDirection();
    m_listBug.push_back(pBug);
}