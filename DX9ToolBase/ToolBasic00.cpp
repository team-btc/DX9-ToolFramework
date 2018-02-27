
// ToolBasic00.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ToolBasic00.h"
#include "MainFrm.h"

#include "ToolBasic00Doc.h"
#include "ToolBasic00View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolBasic00App

BEGIN_MESSAGE_MAP(CToolBasic00App, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &CToolBasic00App::OnAppAbout)
    // ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
    ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

CToolBasic00View *g_pView;
// CToolBasic00App ����

CToolBasic00App::CToolBasic00App()
{
    m_bHiColorIcons = TRUE;

    // TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
    // ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
    SetAppID(_T("ToolBasic00.AppID.NoVersion"));

    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
    // InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CToolBasic00App ��ü�Դϴ�.

CToolBasic00App theApp;


// CToolBasic00App �ʱ�ȭ

BOOL CToolBasic00App::InitInstance()
{
    // ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
    // ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
    // InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
    // �� �׸��� �����Ͻʽÿ�.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinAppEx::InitInstance();


    EnableTaskbarInteraction(FALSE);

    // RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
    // AfxInitRichEdit2();

    // ǥ�� �ʱ�ȭ
    // �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
    // �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
    // ��ƾ�� �����ؾ� �մϴ�.
    // �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
    // TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
    // ������ �������� �����ؾ� �մϴ�.
    SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
    LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


    InitContextMenuManager();

    InitKeyboardManager();

    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
                                                 RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    // ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
    //  ����, ������ â �� �� ������ ���� ������ �մϴ�.
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CToolBasic00Doc),
        RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
        RUNTIME_CLASS(CToolBasic00View));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);


    // ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);



    // ����ٿ� ������ ����� ����ġ�մϴ�.
    // ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    // ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
    //  SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
    return TRUE;
}

// CToolBasic00App �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // ��ȭ ���� �������Դϴ�.
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

                                                        // �����Դϴ�.
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CToolBasic00App::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

// CToolBasic00App ����� ���� �ε�/���� �޼���

void CToolBasic00App::PreLoadState()
{
    BOOL bNameValid;
    CString strName;
    bNameValid = strName.LoadString(IDS_EDIT_MENU);
    ASSERT(bNameValid);
    GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CToolBasic00App::LoadCustomState()
{
}

void CToolBasic00App::SaveCustomState()
{
}

// CToolBasic00App �޽��� ó����





BOOL CToolBasic00App::OnIdle(LONG lCount)
{
    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    if (this->m_pMainWnd->IsIconic())
    {
        return FALSE;
    }
    else
    {
        g_pView->m_GameEdu01.Update();
        g_pView->m_GameEdu01.Render();
    }

    return TRUE;
}


