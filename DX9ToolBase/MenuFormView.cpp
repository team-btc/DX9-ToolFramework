// MenuFormView.cpp : 구현 파일입니다.
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


// CMenuFormView 진단입니다.

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

//MFC 실행될때 초기화되는곳
void CMenuFormView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    //  컨트롤들에 대한 추가 설정값을 입력하는 부분.
	pCreateSkin = NULL;
	g_pView->m_pMainGame->SetMenuFormView(this);
	m_PositionSlider.SetRange(0, 100);
	isClick = false;
	Select = 0;
	CurState = 0;
	CurPositionList = 0;

	char *szTextState[2] = { "번호","이름" };
	int nWid[2] = { 74,200 };
	LV_COLUMN lCol;

	lCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;  //구조체의 기능을 확장할 플래그를 지정
	lCol.fmt = LVCFMT_LEFT;  //칼럼의 정렬을 왼쪽정렬로 지정(_CENTER, _LEFT, _RIGHT중 선택)

	for (int i = 0; i < 2; i++) {

		lCol.pszText = szTextState[i];  //칼럼의 제목을 지정
		lCol.iSubItem = i;  //서브아이템의 인덱스를 지정
		lCol.cx = nWid[i];  //칼럼의 넓이를 지정
		m_PreStateList.InsertColumn(i, &lCol);  //LVCOLUMN구조체로 만들어진 값을 토대로 리스트 컨트롤에 칼럼을 삽입
	}

	char *szTextPos[3] = { "번호","이름","POSITION" };
    int nWidPos[3] = { 40,74,160 };

	for (int i = 0; i < 3; i++) {

		lCol.pszText = szTextPos[i];  //칼럼의 제목을 지정
		lCol.iSubItem = i;  //서브아이템의 인덱스를 지정
		lCol.cx = nWidPos[i];  //칼럼의 넓이를 지정
		m_PositionList.InsertColumn(i, &lCol);  //LVCOLUMN구조체로 만들어진 값을 토대로 리스트 컨트롤에 칼럼을 삽입
	}
	
	m_EditPosition.SetWindowTextA("0");

	//CRichEditCtrl* pWndRich = (CRichEditCtrl*)GetDlgItem(IDC_EDIT_POSITION);
	//pWndRich->SetEventMask(pWndRich->GetEventMask() | ENM_CHANGE);
	//	

}

void CMenuFormView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HRESULT hr;
	if (pCreateSkin)
		hr = pCreateSkin->SetAnimPlay(true);

	g_pView->m_pMainGame->SetText("TEST");
}


void CMenuFormView::OnBnClickedStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HRESULT hr;

	if (pCreateSkin)
	{
		hr = pCreateSkin->SetAnimPlay(false);
	}

	g_pView->m_pMainGame->SetText("");
}


void CMenuFormView::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pCreateSkin)
	{
		m_PositionList.DeleteItem(0);
	}
}



void CMenuFormView::OnNMCustomdrawAnimPositionSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CStringA str;
	int pos = m_PositionSlider.GetPos();
	str.Format("%d", pos);
	g_pView->m_pMainGame->SetText(str);
	*pResult = 0;
}


void CMenuFormView::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

    char name_filter[] = "All Files (*.*)|*.*|json Files (*.json)|*.json|";

    CFileDialog ins_dlg(FALSE, "json", "*.json", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
        OFN_NOCHANGEDIR, name_filter, NULL);

    ins_dlg.m_ofn.nFilterIndex = 2;

    // 다이얼로그를 띄운다.
    if (ins_dlg.DoModal() == IDOK) {
        // 선택한 파일의 이름을 에디트 박스에 출력한다.
       // SetDlgItemText(IDC_FILE_NAME_EDIT, ins_dlg.GetFileName());
        // 선택한 파일의 이름을 포함한 경로를 에디트 박스에 출력한다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

//안씀
void CMenuFormView::OnEnChangeEditPosition()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

//안씀
void CMenuFormView::OnEnChangeEditName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}

//안씀
void CMenuFormView::OnEnChangeEditStateName()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CFormView::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMenuFormView::OnBnClickedButtonInputStateName()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (pCreateSkin)
    {
        CString str;
       
        m_EditStateName.GetWindowTextA(str);
        m_PreStateList.SetItemText(CurState, 1, (LPCTSTR)str);
    }
}


void CMenuFormView::OnEnChangeEditAnimScale()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CFormView::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (pCreateSkin)
    {
        m_EditAnimScale.GetWindowTextA(strScale);
        float Scale = _ttof(strScale);
        pCreateSkin->SetScale(Scale);
    }
}
