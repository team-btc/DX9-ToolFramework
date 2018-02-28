#include "StdAfx.h"
#include "cMainGame.h"
#include <D3dx9math.h>
#include <stdio.h>

cMainGame::cMainGame(void)
    : m_szText("")
    , m_pCamera(NULL)
    , m_pMesh(NULL)
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

    D3DXCreateBox(g_pDevice, 1, 1, 1, &m_pMesh, NULL);
}

void cMainGame::OnUpdate()
{
    g_pTimerManager->Update(60.0f);

    if (m_pCamera)
    {
        m_pCamera->Update();
    }

    if (g_pKeyManager->isStayKeyDown('A'))
    {
        m_vRot.y -= 1.0f;
    }
    else if (g_pKeyManager->isStayKeyDown('D'))
    {
        m_vRot.y += 1.0f;
    }

    if (g_pKeyManager->isStayKeyDown('W'))
    {
        m_vRot.x += 1.0f;
    }
    else if (g_pKeyManager->isStayKeyDown('S'))
    {
        m_vRot.x -= 1.0f;
    }
}

void cMainGame::OnRender()
{
    g_pTimerManager->Render();

    if (m_pMesh)
    {
        Matrix4 matR;
        D3DXMatrixRotationYawPitchRoll(&matR,
                                       D3DXToRadian(m_vRot.y),
                                       D3DXToRadian(m_vRot.x),
                                       D3DXToRadian(m_vRot.z));
        g_pDevice->SetTransform(D3DTS_WORLD, &matR);
        m_pMesh->DrawSubset(0);
    }
}

void cMainGame::OnRelease()
{
    SAFE_DELETE(m_pCamera);
    SAFE_RELEASE(m_pMesh);
}