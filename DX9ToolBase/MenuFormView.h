#pragma once




// CMenuFormView �� ���Դϴ�.

class CMenuFormView : public CFormView
{
    DECLARE_DYNCREATE(CMenuFormView)

protected:
    CMenuFormView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

    DECLARE_MESSAGE_MAP()
public:



};


