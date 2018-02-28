// MenuFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToolBasic00.h"
#include "MenuFormView.h"

#include "ToolBasic00View.h"

// CMenuFormView

extern CToolBasic00View *g_pView;

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
}

BEGIN_MESSAGE_MAP(CMenuFormView, CFormView)
    ON_BN_CLICKED(IDC_BUTTON1, &CMenuFormView::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_OK_BTN, &CMenuFormView::OnBnClickedOkBtn)
    ON_BN_CLICKED(IDC_CANCEL, &CMenuFormView::OnBnClickedCancel)
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
