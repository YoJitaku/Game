//=============================================================================
//
// [Company.cpp] Draw the name of Company
// Author : JITAKU YO
//
//=============================================================================
#include "Company.h"
#include "Fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCompany = NULL;
LPDIRECT3DTEXTURE9 g_pTextureCompany[COMPANY_COMPONENT] = {};
POLYGON_2D *pCompany;
int g_nCntTime1;
HRESULT InitCompany(void)
{
	g_nCntTime1 = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pCompany = (POLYGON_2D *)malloc(COMPANY_COMPONENT * sizeof(POLYGON_2D));
	
	pCompany[0].bUse = true;
	pCompany[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pCompany[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
	pCompany[1].bUse = true;
	pCompany[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pCompany[1].size = D3DXVECTOR2(WIDTH_SCREEN * 10, HEIGHT_SCREEN * 10);

	//load texture
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/CompanyBackground.png", &g_pTextureCompany[0])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/CompanyLogo.png", &g_pTextureCompany[1])))return E_FAIL;

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * COMPANY_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffCompany, NULL))) return E_FAIL;

	g_pVtxBuffCompany->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < COMPANY_COMPONENT; nCnt++, pVtx+=4)
	{
		pVtx[0].pos = D3DXVECTOR3(pCompany[nCnt].pos.x - pCompany[nCnt].size.x, pCompany[nCnt].pos.y - pCompany[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pCompany[nCnt].pos.x + pCompany[nCnt].size.x, pCompany[nCnt].pos.y - pCompany[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pCompany[nCnt].pos.x - pCompany[nCnt].size.x, pCompany[nCnt].pos.y + pCompany[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pCompany[nCnt].pos.x + pCompany[nCnt].size.x, pCompany[nCnt].pos.y + pCompany[nCnt].size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
	}
	g_pVtxBuffCompany->Unlock();
	return S_OK;
}
void UninitCompany(void)
{
	if (g_pVtxBuffCompany != NULL)
	{
		g_pVtxBuffCompany->Release();
		g_pVtxBuffCompany = NULL;
	}
	for (int nCnt = 0; nCnt < COMPANY_COMPONENT; nCnt++)
	{
		if (g_pTextureCompany[nCnt] != NULL)
		{			 
			g_pTextureCompany[nCnt]->Release();
			g_pTextureCompany[nCnt] = NULL;
		}
	}
	free(pCompany);
}

void UpdateCompany(void)
{
	g_nCntTime1++;
	VERTEX_2D *pVtx;
	if (pCompany[1].size.x > WIDTH_SCREEN / 2)
	{
		pCompany[1].size.x -= (WIDTH_SCREEN * 10) / 100;
		pCompany[1].size.y -= (HEIGHT_SCREEN * 10) / 100;
	}
	if (g_nCntTime1 > 200)
		SetFade(FADE_OUT, MODE_TITLE);

	g_pVtxBuffCompany->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[4].pos = D3DXVECTOR3(pCompany[1].pos.x - pCompany[1].size.x, pCompany[1].pos.y - pCompany[1].size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(pCompany[1].pos.x + pCompany[1].size.x, pCompany[1].pos.y - pCompany[1].size.y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(pCompany[1].pos.x - pCompany[1].size.x, pCompany[1].pos.y + pCompany[1].size.y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(pCompany[1].pos.x + pCompany[1].size.x, pCompany[1].pos.y + pCompany[1].size.y, 0.0f);
	g_pVtxBuffCompany->Unlock();
}

void DrawCompany(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffCompany, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < COMPANY_COMPONENT; nCnt++)
	{
		if (pCompany[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureCompany[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}