//=============================================================================
//
// [Menu.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "Menu.h"
#include "Fade.h"
#include "Dinput8.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenu = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMenu[MENU_COMPONENT] = {};
POLYGON_2D *pMenu;
int g_nCntTime3;
HRESULT InitMenu(void)
{
	g_nCntTime3 = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pMenu = (POLYGON_2D *)malloc(MENU_COMPONENT * sizeof(POLYGON_2D));

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/MenuBackGround.png", &g_pTextureMenu[0])))return E_FAIL;
	pMenu[0].bUse = true;
	pMenu[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pMenu[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/SelectHand.png", &g_pTextureMenu[1])))return E_FAIL;
	pMenu[1].bUse = true;
	pMenu[1].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 , HEIGHT_SCREEN / 2 - 150, 0);
	pMenu[1].size = D3DXVECTOR2(WIDTH_SCREEN / 12, HEIGHT_SCREEN / 4);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/Start.png", &g_pTextureMenu[2])))return E_FAIL;
	pMenu[2].bUse = true;
	pMenu[2].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 300, HEIGHT_SCREEN / 2 - 150, 0);
	pMenu[2].size = D3DXVECTOR2(WIDTH_SCREEN / 12, HEIGHT_SCREEN / 8);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/Tutorial.png", &g_pTextureMenu[3])))return E_FAIL;
	pMenu[3].bUse = false;
	pMenu[3].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 300, HEIGHT_SCREEN / 2, 0);
	pMenu[3].size = D3DXVECTOR2(WIDTH_SCREEN / 12, HEIGHT_SCREEN / 8);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/Ranking.png", &g_pTextureMenu[4])))return E_FAIL;
	pMenu[4].bUse = true;
	pMenu[4].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 300, HEIGHT_SCREEN / 2, 0);
	pMenu[4].size = D3DXVECTOR2(WIDTH_SCREEN / 12, HEIGHT_SCREEN / 8);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/Exit.png", &g_pTextureMenu[5])))return E_FAIL;
	pMenu[5].bUse = true;
	pMenu[5].pos = D3DXVECTOR3(WIDTH_SCREEN / 2 + 300, HEIGHT_SCREEN / 2 + 150, 0);
	pMenu[5].size = D3DXVECTOR2(WIDTH_SCREEN / 12, HEIGHT_SCREEN / 8);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/Effect1.png", &g_pTextureMenu[6])))return E_FAIL;
	pMenu[6].bUse = false;
	pMenu[6].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pMenu[6].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/Effect2.png", &g_pTextureMenu[7])))return E_FAIL;
	pMenu[7].bUse = false;
	pMenu[7].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pMenu[7].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MENU_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMenu, NULL))) return E_FAIL;

	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MENU_COMPONENT; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pMenu[nCnt].pos.x - pMenu[nCnt].size.x, pMenu[nCnt].pos.y - pMenu[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pMenu[nCnt].pos.x + pMenu[nCnt].size.x, pMenu[nCnt].pos.y - pMenu[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pMenu[nCnt].pos.x - pMenu[nCnt].size.x, pMenu[nCnt].pos.y + pMenu[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pMenu[nCnt].pos.x + pMenu[nCnt].size.x, pMenu[nCnt].pos.y + pMenu[nCnt].size.y, 0.0f);
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
	g_pVtxBuffMenu->Unlock();

	return S_OK;
}

void UninitMenu(void)
{
	if (g_pVtxBuffMenu != NULL)
	{			 
		g_pVtxBuffMenu->Release();
		g_pVtxBuffMenu = NULL;
	}
	for (int nCnt = 0; nCnt < MENU_COMPONENT; nCnt++)
	{
		if (g_pTextureMenu[nCnt] != NULL)
		{			  
			g_pTextureMenu[nCnt]->Release();
			g_pTextureMenu[nCnt] = NULL;
		}
	}
	free(pMenu);
}

void UpdateMenu(void)
{
	VERTEX_2D *pVtx;
	g_nCntTime3++;

	if (GetkeyboardTrigger(DIK_UP) == true)
	{
		pMenu[1].pos.y -= 150;
		if (pMenu[1].pos.y < HEIGHT_SCREEN / 2 - 150) pMenu[1].pos.y = HEIGHT_SCREEN / 2 + 150;
	}
	if (GetkeyboardTrigger(DIK_DOWN) == true)
	{
		pMenu[1].pos.y += 150;
		if (pMenu[1].pos.y > HEIGHT_SCREEN / 2 + 150) pMenu[1].pos.y = HEIGHT_SCREEN / 2 - 150;
	}

	if (GetkeyboardTrigger(DIK_RETURN) == true)
	{
		int nPosy = (int)pMenu[1].pos.y;
		switch (nPosy)
		{
		case  HEIGHT_SCREEN / 2 - 150:
			SetFade(FADE_OUT, MODE_GAME);
			break;
		case  HEIGHT_SCREEN / 2:
			SetFade(FADE_OUT, MODE_RANKING);
			break;
		case  HEIGHT_SCREEN / 2 + 150:
			PostQuitMessage(0);
			break;
		}
	}

	g_pVtxBuffMenu->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < MENU_COMPONENT; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pMenu[nCnt].pos.x - pMenu[nCnt].size.x, pMenu[nCnt].pos.y - pMenu[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pMenu[nCnt].pos.x + pMenu[nCnt].size.x, pMenu[nCnt].pos.y - pMenu[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pMenu[nCnt].pos.x - pMenu[nCnt].size.x, pMenu[nCnt].pos.y + pMenu[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pMenu[nCnt].pos.x + pMenu[nCnt].size.x, pMenu[nCnt].pos.y + pMenu[nCnt].size.y, 0.0f);
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
	g_pVtxBuffMenu->Unlock();
}

void DrawMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffMenu, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MENU_COMPONENT; nCnt++)
	{
		if (pMenu[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureMenu[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}