#include "StdAfx.h"
#include "cMainGame.h"
#include <D3dx9math.h>
#include <stdio.h>

cMainGame::cMainGame(void)
    : m_szText("")
    , m_pCamera(NULL)
    , m_pSkinMesh(NULL)
	, m_pMenuFormView(NULL)
    , m_vRot(0, 0, 0)
{
}


cMainGame::~cMainGame(void)
{
}

void cMainGame::OnInit()
{
    g_pKeyManager->Setup();

    m_pCamera = new cCamera;
    m_pCamera->Setup(m_hWnd);

    D3DXCreateBox(g_pDevice, 1, 1, 1, &m_pBox, NULL);
}

void cMainGame::OnUpdate()
{
    g_pTimerManager->Update(60.0f);

    if (m_pCamera)
    {
        
            m_pCamera->Update();
    }

	//쓰는이유: MenuFormView에 업데이트가 없어서..
	if (m_pMenuFormView && m_pSkinMesh)
	{
		bool Play;
		m_pSkinMesh->GetAnimPlay(&Play);
		if (Play) 
		{
			float TotalPos = 0, CurPos = 0;
			m_pSkinMesh->GetAnimTotalPosition(&TotalPos);
			m_pSkinMesh->GetAnimCurPosition(&CurPos);
			int pos = CurPos / TotalPos * 100;

			m_pMenuFormView->SetSliderBar(pos);
		}

		//에딧포지션에 현재 포지션이 업데이트
		CString str;
		float fCurPos;
		m_pSkinMesh->GetAnimCurPosition(&fCurPos);

		str.Format(_T("%f"), fCurPos);
		m_pMenuFormView->m_EditPosition.SetWindowTextA(str);
	}
}

void cMainGame::OnRender()
{
    g_pTimerManager->Render();

    Matrix4 matI;
    D3DXMatrixIdentity(&matI);
    g_pDevice->SetTransform(D3DTS_WORLD, &matI);

	RECT rt = { 0, 30, W_WIDTH, W_HEIGHT };
	g_pFontManager->GetFont(cFontManager::E_DEBUG)->DrawTextA(NULL,
		m_szText,
		-1,
		&rt,
		DT_LEFT | DT_NOCLIP,
		D3DCOLOR_XRGB(128, 128, 128));

    m_pBox->DrawSubset(0);
    
    if (m_pSkinMesh)
    {
        m_pSkinMesh->UpdateAndRender();
    }
}

void cMainGame::OnRelease()
{
    SAFE_DELETE(m_pCamera);
}

HRESULT cMainGame::SetSkinedMesh(IN cSkinnedMesh * SkinnedMesh)
{
	HRESULT hr;

	if (SkinnedMesh)
	{
		m_pSkinMesh = SkinnedMesh;
		hr = S_OK;
	}
	else
	{
		hr = E_POINTER;
	}

	return hr;
}

HRESULT cMainGame::SetMenuFormView(IN CMenuFormView * FormView)
{
	HRESULT hr;

	if (FormView)
	{
		m_pMenuFormView = FormView;
		hr = S_OK;
	}
	else
		hr = E_POINTER;

	return hr;
}
