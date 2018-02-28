// MenuFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToolBasic.h"
#include "MenuFormView.h"

#include "ToolBasicView.h"

// CMenuFormView

extern CToolBasicView *g_pView;

IMPLEMENT_DYNCREATE(CMenuFormView, CFormView)

CMenuFormView::CMenuFormView()
    : CFormView(CMenuFormView::IDD)
{
}

CMenuFormView::~CMenuFormView()
{
}

void CMenuFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, ID_SLIDER_TEST, m_sliderTest);
    DDX_Control(pDX, IDC_EDIT_BROWSE, m_editBrowse);
    DDX_Control(pDX, IDC_LIST1, m_listBox);
}

BEGIN_MESSAGE_MAP(CMenuFormView, CFormView)
    ON_BN_CLICKED(IDC_BUTTON1, &CMenuFormView::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_OK_BTN, &CMenuFormView::OnBnClickedOkBtn)
    ON_BN_CLICKED(IDC_CANCEL, &CMenuFormView::OnBnClickedCancel)
    ON_WM_HSCROLL()
    ON_EN_CHANGE(IDC_EDIT_BROWSE, &CMenuFormView::OnEnChangeEditBrowse)
    ON_LBN_SELCHANGE(IDC_LIST1, &CMenuFormView::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CMenuFormView �����Դϴ�.

#ifdef _DEBUG
void CMenuFormView::AssertValid() const
{
    CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMenuFormView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


void CMenuFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    //  ��Ʈ�ѵ鿡 ���� �߰� �������� �Է��ϴ� �κ�.
    m_sliderTest.SetRange(0, 200);

    m_listBox.AddString("test1");
    m_listBox.AddString("test2");
    m_listBox.AddString("test3");
    m_listBox.AddString("test4");
}


// CMenuFormView �޽��� ó�����Դϴ�.
void CMenuFormView::OnBnClickedButton1()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    g_pView->m_pMainGame->SetText("TEST");
}

void CMenuFormView::OnBnClickedOkBtn()
{
    g_pView->m_pMainGame->SetText("");
}

void CMenuFormView::OnBnClickedCancel()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    g_pView->m_pMainGame->SetText("TEST");
}

void CMenuFormView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    if (pScrollBar)
    {
        if ((CScrollBar*)&m_sliderTest == pScrollBar)
        {
            CStringA str;
            int pos = m_sliderTest.GetPos();
            str.Format("%d", pos);
            g_pView->m_pMainGame->SetText(str);
        }
    }
}

void CMenuFormView::OnEnChangeEditBrowse()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CFormView::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CString str;
    m_editBrowse.GetWindowTextA(str);
    g_pView->m_pMainGame->SetText(str);
}


void CMenuFormView::OnLbnSelchangeList1()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

    CString str;
    m_listBox.GetText(m_listBox.GetCurSel(), str);
    g_pView->m_pMainGame->SetText(str);
}
