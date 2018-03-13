
// ToolBasic00View.cpp : CToolBasic00View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CToolBasic00View 생성/소멸

CToolBasicView::CToolBasicView()
{
    // TODO: 여기에 생성 코드를 추가합니다.
    m_isRButtonDown = false;

}

CToolBasicView::~CToolBasicView()
{
    m_pMainGame->Cleanup();
}

BOOL CToolBasicView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: CREATESTRUCT cs를 수정하여 여기에서
    //  Window 클래스 또는 스타일을 수정합니다.

    return CView::PreCreateWindow(cs);
}

// CToolBasic00View 그리기

void CToolBasicView::OnDraw(CDC* /*pDC*/)
{
    CToolBasicDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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


// CToolBasic00View 진단

#ifdef _DEBUG
void CToolBasicView::AssertValid() const
{
    CView::AssertValid();
}

void CToolBasicView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CToolBasicDoc* CToolBasicView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolBasicDoc)));
    return (CToolBasicDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolBasic00View 메시지 처리기


void CToolBasicView::OnInitialUpdate()
{
    CView::OnInitialUpdate();

    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    m_pMainGame = new cMainGame;
    m_pMainGame->InitD3D(m_hWnd);
}


BOOL CToolBasicView::OnEraseBkgnd(CDC* pDC)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    return FALSE;
}

BOOL CToolBasicView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    m_ptPrevMouse.x = point.x;
    m_ptPrevMouse.y = point.y;
    m_isRButtonDown = true;

    CView::OnRButtonDown(nFlags, point);
}


void CToolBasicView::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
    if (m_isRButtonDown)
    {
        POINT ptCurrMouse;
        ptCurrMouse.x = point.x;
        ptCurrMouse.y = point.y;

        m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 5.0f;
        m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 5.0f;

        // x축 회전은 -90 ~ 90 으로 고정
        if (m_fRotX < -D3DX_PI * LIMITED_ROT + D3DX_16F_EPSILON)
            m_fRotX = -D3DX_PI * LIMITED_ROT + D3DX_16F_EPSILON;
        else if (m_fRotX > D3DX_PI * LIMITED_ROT - D3DX_16F_EPSILON)
            m_fRotX = D3DX_PI * LIMITED_ROT - D3DX_16F_EPSILON;

        m_ptPrevMouse = ptCurrMouse;
    }
    CView::OnMouseMove(nFlags, point);
}
