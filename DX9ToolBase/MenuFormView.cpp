// MenuFormView.cpp : 구현 파일입니다.
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


// CMenuFormView 진단입니다.

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


// CMenuFormView 메시지 처리기입니다.




void CMenuFormView::OnBnClickedButton1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    g_pView->m_pMainGame->SetText("TEST");
}

void CMenuFormView::OnBnClickedOkBtn()
{
    g_pView->m_pMainGame->SetText("");
}

void CMenuFormView::OnBnClickedCancel()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    g_pView->m_pMainGame->SetText("TEST");
}
