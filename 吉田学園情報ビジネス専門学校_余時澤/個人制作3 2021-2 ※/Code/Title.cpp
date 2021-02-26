//=============================================================================
//
// [Title.cpp] Draw the name of Game
// Author : JITAKU YO
//
//=============================================================================
#include "Title.h"
#include "Dinput8.h"
#include "Fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_COMPONENT] = {};
POLYGON_2D *pTitle;
int g_nCntTime2, g_nBlinkSpeed, g_nMoveSpeed;
HRESULT InitTitle(void)
{
	g_nCntTime2 = 0;
	g_nBlinkSpeed = 40;
	g_nMoveSpeed = 5;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pTitle = (POLYGON_2D *)malloc(TITLE_COMPONENT * sizeof(POLYGON_2D));

	pTitle[0].bUse = true;
	pTitle[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTitle[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
	pTitle[1].bUse = true;
	pTitle[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, -200, 0);
	pTitle[1].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);
	pTitle[2].bUse = false;
	pTitle[2].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTitle[2].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/TitleBackGround.jpg", &g_pTextureTitle[0])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/GameLogo.png", &g_pTextureTitle[1])))return E_FAIL;
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/PressStart.png", &g_pTextureTitle[2])))return E_FAIL;

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TITLE_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL))) return E_FAIL;

	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < TITLE_COMPONENT; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pTitle[nCnt].pos.x - pTitle[nCnt].size.x, pTitle[nCnt].pos.y - pTitle[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pTitle[nCnt].pos.x + pTitle[nCnt].size.x, pTitle[nCnt].pos.y - pTitle[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pTitle[nCnt].pos.x - pTitle[nCnt].size.x, pTitle[nCnt].pos.y + pTitle[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pTitle[nCnt].pos.x + pTitle[nCnt].size.x, pTitle[nCnt].pos.y + pTitle[nCnt].size.y, 0.0f);
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
	g_pVtxBuffTitle->Unlock();
	return S_OK;
}

void UninitTitle(void)
{
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	for (int nCnt = 0; nCnt < TITLE_COMPONENT; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
	free(pTitle);
}

void UpdateTitle(void)
{
	g_nCntTime2++;
	VERTEX_2D *pVtx;

	if (pTitle[1].pos.y < HEIGHT_SCREEN / 2)  pTitle[1].pos.y += g_nMoveSpeed;
	if (g_nCntTime2 % g_nBlinkSpeed == 0 && pTitle[1].pos.y >= HEIGHT_SCREEN / 2)
		pTitle[2].bUse = !pTitle[2].bUse;

	if (GetkeyboardRelease(DIK_RETURN) == true && pTitle[1].pos.y >= HEIGHT_SCREEN / 2)
	{
		g_nBlinkSpeed = 5;
		SetFade(FADE_OUT, MODE_MENU);
	}

	if (GetkeyboardRelease(DIK_RETURN) == true)
		g_nMoveSpeed = 50;

	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[4].pos = D3DXVECTOR3(pTitle[1].pos.x - pTitle[1].size.x, pTitle[1].pos.y - pTitle[1].size.y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(pTitle[1].pos.x + pTitle[1].size.x, pTitle[1].pos.y - pTitle[1].size.y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(pTitle[1].pos.x - pTitle[1].size.x, pTitle[1].pos.y + pTitle[1].size.y, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(pTitle[1].pos.x + pTitle[1].size.x, pTitle[1].pos.y + pTitle[1].size.y, 0.0f);
	g_pVtxBuffTitle->Unlock();
}

void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TITLE_COMPONENT; nCnt++)
	{
		if (pTitle[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTitle[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
