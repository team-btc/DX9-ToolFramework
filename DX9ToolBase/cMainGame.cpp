#include "StdAfx.h"
#include "cMainGame.h"
#include <D3dx9math.h>
#include <stdio.h>

cMainGame::cMainGame(void)
{
}


cMainGame::~cMainGame(void)
{
}

void cMainGame::OnInit()
{
    int i;

    RECT rect;
    D3DVIEWPORT9 vp;
    GetClientRect(m_hWnd, &rect);

    vp.X = 0;
    vp.Y = 0;
    vp.Width = rect.right - rect.left;  // ÁÂÇ¥°³³äÀÌ ¾Æ´Ï¶ó Å©±â °³³ä 800, 600 °è»êµÊ
    vp.Height = rect.bottom - rect.top;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;

    m_Eye.x = 0.0f;
    m_Eye.y = 10.0f;
    m_Eye.z = -32.0f;

    m_At.x = 0.0f;
    m_At.y = 0.0f;
    m_At.z = 0.0f;

    m_Up.x = 0.0f;
    m_Up.y = 1.0f;
    m_Up.z = 0.0f;

    D3DXMatrixLookAtLH(&m_matView, &m_Eye, &m_At, &m_Up);
    m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView);

    D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
    m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
    m_pd3dDevice->SetViewport(&vp);

    D3DXCreateFont(m_pd3dDevice, 20, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
                   OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                   "System", &m_pFont);

    D3DXCreateFont(m_pd3dDevice, 30, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET,
                   OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                   "µ¸¿òÃ¼", &m_pFont2);

    m_nFPSCount = 0;
    m_nFPS = 0;
}

void cMainGame::OnRender()
{
    char string[100];
    RECT rt;
    SetRect(&rt, 10, 10, 0, 0);
    sprintf_s(string, -1, "FPS: %d", m_nFPS);
    m_pFont->DrawText(NULL, string, -1, &rt, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
}

void cMainGame::OnUpdate()
{
    DWORD dwCurTime = GetTickCount();
    static DWORD dwOldTime = dwCurTime;
    static DWORD dwAccumulateTime = 0; // ´©Àû ½Ã°£
    m_dwElapsedTime = dwCurTime - dwOldTime;
    dwOldTime = dwCurTime;

    dwAccumulateTime += m_dwElapsedTime;
    if (dwAccumulateTime >= 1000)
    {
        dwAccumulateTime = 0;
        m_nFPS = m_nFPSCount;
        m_nFPSCount = 0;
    }
    else
    {
        m_nFPSCount++;
    }
}

void cMainGame::OnRelease()
{
    m_pFont->Release();
    m_pFont2->Release();
}