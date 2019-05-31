// BugHunt9102.cpp: 定义应用程序的类行为。
//

#include "pch.h"

#include "BugHunt9102.h"
#include "MainFrm.h"
#include "afxdialogex.h"
#include "afxwinappex.h"
#include "framework.h"

#include "BugHunt9102Doc.h"
#include "BugHunt9102View.h"

#ifdef _DEBUG
#    define new DEBUG_NEW
#endif

// CBugHunt9102App

BEGIN_MESSAGE_MAP(CBugHunt9102App, CWinApp)
ON_COMMAND(ID_APP_ABOUT, &CBugHunt9102App::OnAppAbout)
// 基于文件的标准文档命令
ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()

// CBugHunt9102App 构造

CBugHunt9102App::CBugHunt9102App() noexcept {
    // TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
    //为 CompanyName.ProductName.SubProduct.VersionInformation
    SetAppID(_T("BugHunt9102.AppID.NoVersion"));

    // TODO:  在此处添加构造代码，
    // 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CBugHunt9102App 对象

CBugHunt9102App theApp;

// CBugHunt9102App 初始化

BOOL CBugHunt9102App::InitInstance() {
    CWinApp::InitInstance();

    EnableTaskbarInteraction(FALSE);

    // 使用 RichEdit 控件需要 AfxInitRichEdit2()
    // AfxInitRichEdit2();

    // 标准初始化
    // 如果未使用这些功能并希望减小
    // 最终可执行文件的大小，则应移除下列
    // 不需要的特定初始化例程
    // 更改用于存储设置的注册表项
    // TODO: 应适当修改该字符串，
    // 例如修改为公司或组织名
    SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
    LoadStdProfileSettings(4); // 加载标准 INI 文件选项(包括 MRU)

    // 注册应用程序的文档模板。  文档模板
    // 将用作文档、框架窗口和视图之间的连接
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CBugHunt9102Doc),
        RUNTIME_CLASS(CMainFrame), // 主 SDI 框架窗口
        RUNTIME_CLASS(CBugHunt9102View));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    // 分析标准 shell 命令、DDE、打开文件操作的命令行
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // 调度在命令行中指定的命令。  如果
    // 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // 更换一下标题
    m_pMainWnd->SetWindowText(L"BugHunt9102");

    // 唯一的一个窗口已初始化，因此显示它并对其进行更新
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    return TRUE;
}

// CBugHunt9102App 消息处理程序

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx {
  public:
    CAboutDlg() noexcept;

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

  protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

    // 实现
  protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept :
    CDialogEx(IDD_ABOUTBOX) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CBugHunt9102App::OnAppAbout() {
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

// CBugHunt9102App 消息处理程序
