
// DX9ToolBaseView.h: CDX9ToolBaseView 클래스의 인터페이스
//

#pragma once


class CDX9ToolBaseView : public CView
{
protected: // serialization에서만 만들어집니다.
	CDX9ToolBaseView();
	DECLARE_DYNCREATE(CDX9ToolBaseView)

// 특성입니다.
public:
	CDX9ToolBaseDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CDX9ToolBaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DX9ToolBaseView.cpp의 디버그 버전
inline CDX9ToolBaseDoc* CDX9ToolBaseView::GetDocument() const
   { return reinterpret_cast<CDX9ToolBaseDoc*>(m_pDocument); }
#endif

