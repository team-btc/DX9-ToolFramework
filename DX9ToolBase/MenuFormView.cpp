// MenuFormView.cpp : 구현 파일입니다.
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


void CMenuFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    //  컨트롤들에 대한 추가 설정값을 입력하는 부분.
    m_sliderTest.SetRange(0, 200);

    m_listBox.AddString("test1");
    m_listBox.AddString("test2");
    m_listBox.AddString("test3");
    m_listBox.AddString("test4");
}


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

void CMenuFormView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CFormView::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CString str;
    m_editBrowse.GetWindowTextA(str);
    g_pView->m_pMainGame->SetText(str);
}


void CMenuFormView::OnLbnSelchangeList1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    CString str;
    m_listBox.GetText(m_listBox.GetCurSel(), str);
    g_pView->m_pMainGame->SetText(str);
}
