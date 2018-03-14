// MenuFormView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ToolBasic.h"
#include "MenuFormView.h"

#include "ToolBasicView.h"

// CMenuFormView

extern CToolBasicView *g_pView;

IMPLEMENT_DYNCREATE(CMenuFormView, CFormView)

CMenuFormView::CMenuFormView()
    : CFormView(CMenuFormView::IDD)
{
}

CMenuFormView::~CMenuFormView()
{
}

void CMenuFormView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, ID_ANIM_POSITION_SLIDER, m_PositionSlider);
    DDX_Control(pDX, IDC_LOAD_BOX, m_LoadBox);
	DDX_Control(pDX, IDC_LIST_STATE, m_PreStateList);
	DDX_Control(pDX, IDC_LIST_POSITION, m_PositionList);
	DDX_Control(pDX, IDC_EDIT_NAME, m_EditName);
	DDX_Control(pDX, IDC_EDIT_POSITION, m_EditPosition);
    DDX_Control(pDX, IDC_EDIT_STATE_NAME, m_EditStateName);
    DDX_Control(pDX, IDC_EDIT_ANIM_SCALE, m_EditAnimScale);
}

BEGIN_MESSAGE_MAP(CMenuFormView, CFormView)
    ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_LOAD_BOX, &CMenuFormView::OnEnChangeLoadBox)
	ON_BN_CLICKED(IDC_PLAY, &CMenuFormView::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_STOP, &CMenuFormView::OnBnClickedStop)
	ON_BN_CLICKED(IDC_ADD, &CMenuFormView::OnBnClickedAdd)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_ANIM_POSITION_SLIDER, &CMenuFormView::OnNMCustomdrawAnimPositionSlider)
	ON_BN_CLICKED(IDC_SAVE, &CMenuFormView::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BNT_UP, &CMenuFormView::OnBnClickedBntUp)
	ON_BN_CLICKED(IDC_BNT_DOWN, &CMenuFormView::OnBnClickedBntDown)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STATE, &CMenuFormView::OnLvnItemchangedListState)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_POSITION, &CMenuFormView::OnLvnItemchangedListPosition)
	ON_EN_CHANGE(IDC_EDIT_POSITION, &CMenuFormView::OnEnChangeEditPosition)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CMenuFormView::OnEnChangeEditName)
	ON_BN_CLICKED(IDC_MINUS, &CMenuFormView::OnBnClickedMinus)
    ON_EN_CHANGE(IDC_EDIT_STATE_NAME, &CMenuFormView::OnEnChangeEditStateName)
    ON_BN_CLICKED(IDC_BUTTON_INPUT_STATE_NAME, &CMenuFormView::OnBnClickedButtonInputStateName)
    ON_EN_CHANGE(IDC_EDIT_ANIM_SCALE, &CMenuFormView::OnEnChangeEditAnimScale)
END_MESSAGE_MAP()


// CMenuFormView �����Դϴ�.

#ifdef _DEBUG
void CMenuFormView::AssertValid() const
{
    CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMenuFormView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

//MFC ����ɶ� �ʱ�ȭ�Ǵ°�
void CMenuFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    //  ��Ʈ�ѵ鿡 ���� �߰� �������� �Է��ϴ� �κ�.
	pCreateSkin = NULL;
	g_pView->m_pMainGame->SetMenuFormView(this);
	m_PositionSlider.SetRange(0, 100);
	isClick = false;
	Select = 0;
	CurState = 0;
	CurPositionList = 0;

	char *szTextState[2] = { "��ȣ","�̸�" };
	int nWid[2] = { 74,200 };
	LV_COLUMN lCol;

	lCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;  //����ü�� ����� Ȯ���� �÷��׸� ����
	lCol.fmt = LVCFMT_LEFT;  //Į���� ������ �������ķ� ����(_CENTER, _LEFT, _RIGHT�� ����)

	for (int i = 0; i < 2; i++) {

		lCol.pszText = szTextState[i];  //Į���� ������ ����
		lCol.iSubItem = i;  //����������� �ε����� ����
		lCol.cx = nWid[i];  //Į���� ���̸� ����
		m_PreStateList.InsertColumn(i, &lCol);  //LVCOLUMN����ü�� ������� ���� ���� ����Ʈ ��Ʈ�ѿ� Į���� ����
	}

	char *szTextPos[3] = { "��ȣ","�̸�","POSITION" };
    int nWidPos[3] = { 40,74,160 };

	for (int i = 0; i < 3; i++) {

		lCol.pszText = szTextPos[i];  //Į���� ������ ����
		lCol.iSubItem = i;  //����������� �ε����� ����
		lCol.cx = nWidPos[i];  //Į���� ���̸� ����
		m_PositionList.InsertColumn(i, &lCol);  //LVCOLUMN����ü�� ������� ���� ���� ����Ʈ ��Ʈ�ѿ� Į���� ����
	}
	
	m_EditPosition.SetWindowTextA("0");

	//CRichEditCtrl* pWndRich = (CRichEditCtrl*)GetDlgItem(IDC_EDIT_POSITION);
	//pWndRich->SetEventMask(pWndRich->GetEventMask() | ENM_CHANGE);
	//	

}

void CMenuFormView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
    if (pScrollBar)
    {
        if ((CScrollBar*)&m_PositionSlider == pScrollBar)
        {
            CStringA str;
            int pos = m_PositionSlider.GetPos();
            str.Format("%d", pos);

			if (pCreateSkin)
			{
				pCreateSkin->SetSliderBarByAnimPosition(pos);
				m_PositionSlider.SetPos(pos);
			}
			
            g_pView->m_pMainGame->SetText(str);
        }
    }
}

void CMenuFormView::OnEnChangeLoadBox()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HRESULT hr;
	CString str;
	m_LoadBox.GetWindowTextA(str);

	CString TotalFileName, FileName, KeyName, DummyName;
	int curpos = 0;

	TotalFileName = str;

	FileName = str.Tokenize(_T("\\"), curpos);
	while (FileName != _T(""))
	{
		DummyName = FileName;
		FileName = str.Tokenize(_T("\\"), curpos);
	};
	FileName = DummyName;
	KeyName = DummyName;

	int i = KeyName.ReverseFind('.');
	KeyName = KeyName.Left(i);

	PathRemoveFileSpec((LPSTR)TotalFileName.GetString());

	if (g_pMeshManager->GetMesh(KeyName.GetString()))
	{
		pCreateSkin = g_pMeshManager->GetMesh(KeyName.GetString());
	}
	else
	{
		pCreateSkin = new cSkinnedMesh(KeyName.GetString(), TotalFileName.GetString(), FileName.GetString());
		g_pAutoReleasePool->AddObject(pCreateSkin);
	}

	if (hr = g_pView->m_pMainGame->SetSkinedMesh(pCreateSkin));


	m_PreStateList.DeleteAllItems();
	int StateCount;
	if (hr = pCreateSkin->GetStateCount(&StateCount));
	for (int i = 0; i < StateCount; i++)
	{
		LVITEM Item;
		Item.mask = LVIF_TEXT;
		Item.iItem = i;
		Item.iSubItem = 0;
		char buffer[8];
		sprintf(buffer, "%d", i);
		Item.pszText = (LPSTR)buffer;
		m_PreStateList.InsertItem(&Item);

		LVITEM Item2;
		Item2.mask = LVIF_TEXT;
		Item2.iItem = i;
		Item2.iSubItem = 1;
		string name;
		if (hr = pCreateSkin->GetStateName(&name, i));
		Item2.pszText = (LPSTR)name.c_str();
		m_PreStateList.SetItem(&Item2);
	}

	m_PositionList.DeleteAllItems();
}


void CMenuFormView::OnBnClickedPlay()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HRESULT hr;
	if (pCreateSkin)
		hr = pCreateSkin->SetAnimPlay(true);

	g_pView->m_pMainGame->SetText("TEST");
}


void CMenuFormView::OnBnClickedStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	HRESULT hr;

	if (pCreateSkin)
	{
		hr = pCreateSkin->SetAnimPlay(false);
	}

	g_pView->m_pMainGame->SetText("");
}


void CMenuFormView::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString State,Name,Position;

	if (pCreateSkin)
	{
		m_EditName.GetWindowTextA(Name);
		m_EditPosition.GetWindowTextA(Position);
        State.Format(_T("%d"), CurState);


		LVITEM Item;
		Item.mask = LVIF_TEXT;
		Item.iItem = 0;
		Item.iSubItem = 0;
		Item.pszText = (LPSTR)State.GetString();
		m_PositionList.InsertItem(&Item);

		Item.iSubItem = 1;
		Item.pszText = (LPSTR)Name.GetString();
		m_PositionList.SetItem(&Item);

		Item.iSubItem = 2;
		Item.pszText = (LPSTR)Position.GetString();
		m_PositionList.SetItem(&Item);
	}

}

void CMenuFormView::OnBnClickedMinus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (pCreateSkin)
	{
		m_PositionList.DeleteItem(0);
	}
}



void CMenuFormView::OnNMCustomdrawAnimPositionSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CStringA str;
	int pos = m_PositionSlider.GetPos();
	str.Format("%d", pos);
	g_pView->m_pMainGame->SetText(str);
	*pResult = 0;
}


void CMenuFormView::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

    char name_filter[] = "All Files (*.*)|*.*|json Files (*.json)|*.json|";

    CFileDialog ins_dlg(FALSE, "json", "*.json", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
        OFN_NOCHANGEDIR, name_filter, NULL);

    ins_dlg.m_ofn.nFilterIndex = 2;

    // ���̾�α׸� ����.
    if (ins_dlg.DoModal() == IDOK) {
        // ������ ������ �̸��� ����Ʈ �ڽ��� ����Ѵ�.
       // SetDlgItemText(IDC_FILE_NAME_EDIT, ins_dlg.GetFileName());
        // ������ ������ �̸��� ������ ��θ� ����Ʈ �ڽ��� ����Ѵ�.
        //SetDlgItemText(IDC_FILE_PATH_EDIT, ins_dlg.GetPathName());
        CString str = ins_dlg.GetPathName();

        json SaveFile;

        SaveFile["Scale"] = strScale.GetString();
        for (int i = 0; i < m_PreStateList.GetItemCount(); i++)
        {
            CString StateNum, StateName;
            StateNum = m_PreStateList.GetItemText(i, 0);
            StateName = m_PreStateList.GetItemText(i, 1);

            SaveFile["State"][i]["index"] = StateNum.GetString();
            SaveFile["State"][i]["Name"] = StateName.GetString();
            for (int j = 0; j < m_PositionList.GetItemCount(); j++)
            {
                CString PositionIndex, PositionName, PositionValue;
                PositionIndex = m_PositionList.GetItemText(j, 0);
                if (StateNum == PositionIndex)
                {
                    PositionName = m_PositionList.GetItemText(j, 1);
                    PositionValue = m_PositionList.GetItemText(j, 2);
                    SaveFile["State"][i]["Position"][j]["Name"] = PositionName.GetString();
                    SaveFile["State"][i]["Position"][j]["Value"] = PositionValue.GetString();
                }
            }
        }

        ofstream File;
        File.open(str.GetString());
        File << SaveFile.dump(4);
        File.close();
    }
}

HRESULT CMenuFormView::SetSliderBar(IN int Pos)
{
	HRESULT hr = S_OK;

	m_PositionSlider.SetPos(Pos);

	return hr;
}


void CMenuFormView::OnBnClickedBntUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (pCreateSkin)
	{
		if (Select != 0 && isClick)
		{
			HRESULT hr;
		
			m_PreStateList.DeleteItem(Select);

			LVITEM Item;
			Item.mask = LVIF_TEXT;
			Item.iItem = Select - 1;
			Item.iSubItem = 0;
			char buffer[8];
			sprintf(buffer, "%d", CurState);
			Item.pszText = (LPSTR)buffer;
			m_PreStateList.InsertItem(&Item);

			LVITEM Item2;
			Item2.mask = LVIF_TEXT;
			Item2.iItem = Select - 1;
			Item2.iSubItem = 1;
			string name;
			if (hr = pCreateSkin->GetStateName(&name, CurState));
			Item2.pszText = (LPSTR)name.c_str();
			m_PreStateList.SetItem(&Item2);
			isClick = false;
		}
	}
}


void CMenuFormView::OnBnClickedBntDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (pCreateSkin)
	{
		HRESULT hr;
		int StateCount;
		hr = pCreateSkin->GetStateCount(&StateCount);
		if (Select != StateCount-1 && isClick)
		{
			m_PreStateList.DeleteItem(Select);

			LVITEM Item;
			Item.mask = LVIF_TEXT;
			Item.iItem = Select + 1;
			Item.iSubItem = 0;
			char buffer[8];
			sprintf(buffer, "%d", CurState);
			Item.pszText = (LPSTR)buffer;
			m_PreStateList.InsertItem(&Item);

			LVITEM Item2;
			Item2.mask = LVIF_TEXT;
			Item2.iItem = Select + 1;
			Item2.iSubItem = 1;
			string name;
			if (hr = pCreateSkin->GetStateName(&name, CurState));
			Item2.pszText = (LPSTR)name.c_str();
			m_PreStateList.SetItem(&Item2);
			isClick = false;
		}
	}
}


void CMenuFormView::OnLvnItemchangedListState(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (pNMLV->uChanged == LVIF_STATE && pNMLV->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
	{
		HRESULT hr;
		Select = pNMLV->iItem;
		CString str = m_PreStateList.GetItemText(Select, 1);
		CurState = _ttoi(m_PreStateList.GetItemText(Select, 0));

		if (pCreateSkin)
			hr = pCreateSkin->SetChangeAnim(CurState);

		g_pView->m_pMainGame->SetText(str);
		isClick = true;
	}
	*pResult = 0;
}


void CMenuFormView::OnLvnItemchangedListPosition(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (pNMLV->uChanged == LVIF_STATE && pNMLV->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
	{
        HRESULT hr;
		CurPositionList = pNMLV->iItem;
        int State = _ttoi(m_PositionList.GetItemText(CurPositionList, 0));
        CString str = m_PreStateList.GetItemText(State, 1);

        if (pCreateSkin)
        {
            hr = pCreateSkin->SetChangeAnim(State);
            float pos = _ttof(m_PositionList.GetItemText(CurPositionList, 2));
            hr = pCreateSkin->SetStatePos(pos);
        }
      
	}
	*pResult = 0;
}

//�Ⱦ�
void CMenuFormView::OnEnChangeEditPosition()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}

//�Ⱦ�
void CMenuFormView::OnEnChangeEditName()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
}

//�Ⱦ�
void CMenuFormView::OnEnChangeEditStateName()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CFormView::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMenuFormView::OnBnClickedButtonInputStateName()
{
    // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    if (pCreateSkin)
    {
        CString str;
       
        m_EditStateName.GetWindowTextA(str);
        m_PreStateList.SetItemText(CurState, 1, (LPCTSTR)str);
    }
}


void CMenuFormView::OnEnChangeEditAnimScale()
{
    // TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
    // CFormView::OnInitDialog() �Լ��� ������ 
    //�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
    // �� �˸� �޽����� ������ �ʽ��ϴ�.

    // TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    if (pCreateSkin)
    {
        m_EditAnimScale.GetWindowTextA(strScale);
        float Scale = _ttof(strScale);
        pCreateSkin->SetScale(Scale);
    }
}
