
// ToolBasic00.h : ToolBasic00 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CToolBasic00App:
// �� Ŭ������ ������ ���ؼ��� ToolBasic00.cpp�� �����Ͻʽÿ�.
//

class CToolBasic00App : public CWinAppEx
{
public:
    CToolBasic00App();


    // �������Դϴ�.
public:
    virtual BOOL InitInstance();

    // �����Դϴ�.
    UINT  m_nAppLook;
    BOOL  m_bHiColorIcons;

    virtual void PreLoadState();
    virtual void LoadCustomState();
    virtual void SaveCustomState();

    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
    virtual BOOL OnIdle(LONG lCount);
};

extern CToolBasic00App theApp;
