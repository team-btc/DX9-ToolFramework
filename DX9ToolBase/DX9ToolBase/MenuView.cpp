// MenuView.cpp: 구현 파일
//

#include "stdafx.h"
#include "DX9ToolBase.h"
#include "MenuView.h"


// MenuView

IMPLEMENT_DYNCREATE(MenuView, CView)

MenuView::MenuView()
{

}

MenuView::~MenuView()
{
}

BEGIN_MESSAGE_MAP(MenuView, CView)
END_MESSAGE_MAP()


// MenuView 그리기

void MenuView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// MenuView 진단

#ifdef _DEBUG
void MenuView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MenuView 메시지 처리기
