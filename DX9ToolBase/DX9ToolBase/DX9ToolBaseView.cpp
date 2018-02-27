
// DX9ToolBaseView.cpp: CDX9ToolBaseView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DX9ToolBase.h"
#endif

#include "DX9ToolBaseDoc.h"
#include "DX9ToolBaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDX9ToolBaseView

IMPLEMENT_DYNCREATE(CDX9ToolBaseView, CView)

BEGIN_MESSAGE_MAP(CDX9ToolBaseView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDX9ToolBaseView 생성/소멸

CDX9ToolBaseView::CDX9ToolBaseView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDX9ToolBaseView::~CDX9ToolBaseView()
{
}

BOOL CDX9ToolBaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CDX9ToolBaseView 그리기

void CDX9ToolBaseView::OnDraw(CDC* /*pDC*/)
{
	CDX9ToolBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CDX9ToolBaseView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDX9ToolBaseView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDX9ToolBaseView 진단

#ifdef _DEBUG
void CDX9ToolBaseView::AssertValid() const
{
	CView::AssertValid();
}

void CDX9ToolBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDX9ToolBaseDoc* CDX9ToolBaseView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDX9ToolBaseDoc)));
	return (CDX9ToolBaseDoc*)m_pDocument;
}
#endif //_DEBUG


// CDX9ToolBaseView 메시지 처리기
