
// ToolBasic00View.cpp : CToolBasic00View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ToolBasic00.h"
#endif

#include "ToolBasic00Doc.h"
#include "ToolBasic00View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CToolBasic00View

IMPLEMENT_DYNCREATE(CToolBasic00View, CView)

BEGIN_MESSAGE_MAP(CToolBasic00View, CView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CToolBasic00View ����/�Ҹ�

CToolBasic00View::CToolBasic00View()
{
    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.


}

CToolBasic00View::~CToolBasic00View()
{
    m_pMainGame->Cleanup();
}

BOOL CToolBasic00View::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
    //  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

    return CView::PreCreateWindow(cs);
}

// CToolBasic00View �׸���

void CToolBasic00View::OnDraw(CDC* /*pDC*/)
{
    CToolBasic00Doc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void CToolBasic00View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CToolBasic00View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CToolBasic00View ����

#ifdef _DEBUG
void CToolBasic00View::AssertValid() const
{
    CView::AssertValid();
}

void CToolBasic00View::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CToolBasic00Doc* CToolBasic00View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolBasic00Doc)));
    return (CToolBasic00Doc*)m_pDocument;
}
#endif //_DEBUG


// CToolBasic00View �޽��� ó����


void CToolBasic00View::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    m_pMainGame = new cMainGame;
    m_pMainGame->InitD3D(m_hWnd);
}


BOOL CToolBasic00View::OnEraseBkgnd(CDC* pDC)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    return FALSE;
}