#pragma once
#include "afxcmn.h"
#include "afxeditbrowsectrl.h"
#include <string.h>

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

	afx_msg void OnEnChangeLoadBox();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnNMCustomdrawAnimPositionSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedBntUp();
	afx_msg void OnBnClickedBntDown();
	afx_msg void OnEnChangeEditPosition();
	afx_msg void OnEnChangeEditName();
	afx_msg void OnLvnItemchangedListState(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPosition(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEnChangeEditStateName();
    afx_msg void OnBnClickedButtonInputStateName();

public:
    CSliderCtrl m_PositionSlider;
    CMFCEditBrowseCtrl m_LoadBox;
	CListCtrl m_PreStateList;
	CListCtrl m_PositionList;
	CEdit	m_EditName;
	CEdit	m_EditPosition;
    CEdit   m_EditStateName;
	cSkinnedMesh* pCreateSkin;

	bool		isClick;
	int			Select;
	int			CurState;
	int			CurPositionList;

	HRESULT SetSliderBar(IN int Pos);
};


