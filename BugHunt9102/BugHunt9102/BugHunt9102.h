
// BugHunt9102.h: BugHunt9102 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#    error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h" // 主符号

// CBugHunt9102App:
// 有关此类的实现，请参阅 BugHunt9102.cpp
//

class CBugHunt9102App : public CWinApp {
  public:
    CBugHunt9102App() noexcept;

    // 重写
  public:
    virtual BOOL InitInstance();

    // 实现
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CBugHunt9102App theApp;
