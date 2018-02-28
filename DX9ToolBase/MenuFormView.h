#pragma once
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"




// CMenuFormView 폼 뷰입니다.

class CMenuFormView : public CFormView
{
    DECLARE_DYNCREATE(CMenuFormView)

protected:
    CMenuFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
    virtual ~CMenuFormView();

public:
    enum { IDD = IDD_MENUFORMVIEW };
#ifdef _DEBUG
    virtual void AssertValid() const;
#ifndef _WIN32_WCE
    virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();

    afx_msg void OnBnClickedOkBtn();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnEnChangeEditBrowse();
    afx_msg void OnLbnSelchangeList1();

public:
    CSliderCtrl m_sliderTest;
    CMFCEditBrowseCtrl m_editBrowse;
    CListBox m_listBox;
};


