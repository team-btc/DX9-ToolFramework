
// DX9-ToolFrameworkView.cpp: CDX9ToolFrameworkView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "DX9-ToolFramework.h"
#endif

#include "DX9-ToolFrameworkDoc.h"
#include "DX9-ToolFrameworkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDX9ToolFrameworkView

IMPLEMENT_DYNCREATE(CDX9ToolFrameworkView, CFormView)

BEGIN_MESSAGE_MAP(CDX9ToolFrameworkView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDX9ToolFrameworkView 생성/소멸

CDX9ToolFrameworkView::CDX9ToolFrameworkView()
	: CFormView(IDD_DX9TOOLFRAMEWORK_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CDX9ToolFrameworkView::~CDX9ToolFrameworkView()
{
}

void CDX9ToolFrameworkView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CDX9ToolFrameworkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CDX9ToolFrameworkView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CDX9ToolFrameworkView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDX9ToolFrameworkView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDX9ToolFrameworkView 진단

#ifdef _DEBUG
void CDX9ToolFrameworkView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDX9ToolFrameworkView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDX9ToolFrameworkDoc* CDX9ToolFrameworkView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDX9ToolFrameworkDoc)));
	return (CDX9ToolFrameworkDoc*)m_pDocument;
}
#endif //_DEBUG


// CDX9ToolFrameworkView 메시지 처리기
