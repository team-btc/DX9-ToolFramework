
// ToolBasic00Doc.h : CToolBasic00Doc Ŭ������ �������̽�
//


#pragma once


class CToolBasic00Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
    CToolBasic00Doc();
    DECLARE_DYNCREATE(CToolBasic00Doc)

    // Ư���Դϴ�.
public:

    // �۾��Դϴ�.
public:

    // �������Դϴ�.
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

    // �����Դϴ�.
public:
    virtual ~CToolBasic00Doc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // ������ �޽��� �� �Լ�
protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
