
// ToolBasic00Doc.cpp : CToolBasic00Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ToolBasic00.h"
#endif

#include "ToolBasic00Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CToolBasic00Doc

IMPLEMENT_DYNCREATE(CToolBasic00Doc, CDocument)

BEGIN_MESSAGE_MAP(CToolBasic00Doc, CDocument)
END_MESSAGE_MAP()


// CToolBasic00Doc ����/�Ҹ�

CToolBasic00Doc::CToolBasic00Doc()
{
    // TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CToolBasic00Doc::~CToolBasic00Doc()
{
}

BOOL CToolBasic00Doc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
    // SDI ������ �� ������ �ٽ� ����մϴ�.

    return TRUE;
}




// CToolBasic00Doc serialization

void CToolBasic00Doc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
    }
    else
    {
        // TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
    }
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CToolBasic00Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CToolBasic00Doc::InitializeSearchContent()
{
    CString strSearchContent;
    // ������ �����Ϳ��� �˻� �������� �����մϴ�.
    // ������ �κ��� ";"�� ���еǾ�� �մϴ�.

    // ��: strSearchContent = _T("point;rectangle;circle;ole object;");
    SetSearchContent(strSearchContent);
}

void CToolBasic00Doc::SetSearchContent(const CString& value)
{
    if (value.IsEmpty())
    {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    }
    else
    {
        CMFCFilterChunkValueImpl *pChunk = NULL;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if (pChunk != NULL)
        {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif // SHARED_HANDLERS

// CToolBasic00Doc ����

#ifdef _DEBUG
void CToolBasic00Doc::AssertValid() const
{
    CDocument::AssertValid();
}

void CToolBasic00Doc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG


// CToolBasic00Doc ���
