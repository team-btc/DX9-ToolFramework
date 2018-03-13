
// ToolBasic00View.cpp : CToolBasic00View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ToolBasic.h"
#endif

#include "ToolBasicDoc.h"
#include "ToolBasicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CToolBasic00View

IMPLEMENT_DYNCREATE(CToolBasicView, CView)

BEGIN_MESSAGE_MAP(CToolBasicView, CView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_ERASEBKGND()
    ON_WM_MOUSEWHEEL()
    ON_WM_RBUTTONDOWN()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolBasic00View ����/�Ҹ�

CToolBasicView::CToolBasicView()
{
    // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
    m_isRButtonDown = false;

}

CToolBasicView::~CToolBasicView()
{
    m_pMainGame->Cleanup();
}

BOOL CToolBasicView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
    //  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

    return CView::PreCreateWindow(cs);
}

// CToolBasic00View �׸���

void CToolBasicView::OnDraw(CDC* /*pDC*/)
{
    CToolBasicDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}

void CToolBasicView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
   // OnContextMenu(this, point);
    m_isRButtonDown = false;
}


void CToolBasicView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CToolBasic00View ����

#ifdef _DEBUG
void CToolBasicView::AssertValid() const
{
    CView::AssertValid();
}

void CToolBasicView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CToolBasicDoc* CToolBasicView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolBasicDoc)));
    return (CToolBasicDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolBasic00View �޽��� ó����


void CToolBasicView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    m_pMainGame = new cMainGame;
    m_pMainGame->InitD3D(m_hWnd);
}


BOOL CToolBasicView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    return FALSE;
}

BOOL CToolBasicView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    if (m_fDistance > 2)
    {
        m_fDistance -= zDelta / 100.0f;
    }
    else
    {
        m_fDistance = 2;
        if (zDelta < 0)
            m_fDistance -= zDelta / 100.0f;
    }
    return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CToolBasicView::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    m_ptPrevMouse.x = point.x;
    m_ptPrevMouse.y = point.y;
    m_isRButtonDown = true;

    CView::OnRButtonDown(nFlags, point);
}


void CToolBasicView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    if (m_isRButtonDown)
    {
        POINT ptCurrMouse;
        ptCurrMouse.x = point.x;
        ptCurrMouse.y = point.y;

        m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 5.0f;
        m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 5.0f;

        // x�� ȸ���� -90 ~ 90 ���� ����
        if (m_fRotX < -D3DX_PI * LIMITED_ROT + D3DX_16F_EPSILON)
            m_fRotX = -D3DX_PI * LIMITED_ROT + D3DX_16F_EPSILON;
        else if (m_fRotX > D3DX_PI * LIMITED_ROT - D3DX_16F_EPSILON)
            m_fRotX = D3DX_PI * LIMITED_ROT - D3DX_16F_EPSILON;

        m_ptPrevMouse = ptCurrMouse;
    }
    CView::OnMouseMove(nFlags, point);
}
