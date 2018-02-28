#pragma once
#include "d3dapp.h"
#include <d3dx9math.h>
#include <D3dx9shape.h>

class cMainGame : public CD3DApp
{
private:
    D3DXMATRIX m_matView;
    D3DXMATRIX m_matProj;
    D3DXVECTOR3 m_Eye, m_At, m_Up;

    // ÆùÆ®
    LPD3DXFONT m_pFont;
    LPD3DXFONT m_pFont2;

    DWORD m_dwElapsedTime;
    unsigned int m_nFPS, m_nFPSCount;

    CStringA m_szText;

public:
    cMainGame(void);
    ~cMainGame(void);

private:
    virtual void OnInit();
    virtual void OnRender();
    virtual void OnUpdate();
    virtual void OnRelease();

public:
    void SetText(CStringA szText) { m_szText = szText; }
};

