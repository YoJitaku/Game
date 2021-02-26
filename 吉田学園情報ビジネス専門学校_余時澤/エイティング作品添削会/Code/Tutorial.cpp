//=============================================================================
//
// [Tutorial.cpp] Draw the name of Game
// Author : JITAKU YO
//
//=============================================================================
#include "Tutorial.h"
#include "Dinput8.h"
#include "Fade.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;
LPDIRECT3DTEXTURE9 g_pTextureTutorial[TUTORIAL_COMPONENT] = {};
POLYGON_2D *pTutorial;

HRESULT InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pTutorial = (POLYGON_2D *)malloc(TUTORIAL_COMPONENT * sizeof(POLYGON_2D));

	pTutorial[0].bUse = true;
	pTutorial[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pTutorial[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/TutorialBackground.png", &g_pTextureTutorial[0])))return E_FAIL;

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TUTORIAL_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL))) return E_FAIL;

	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < TUTORIAL_COMPONENT; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(pTutorial[nCnt].pos.x - pTutorial[nCnt].size.x, pTutorial[nCnt].pos.y - pTutorial[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pTutorial[nCnt].pos.x + pTutorial[nCnt].size.x, pTutorial[nCnt].pos.y - pTutorial[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pTutorial[nCnt].pos.x - pTutorial[nCnt].size.x, pTutorial[nCnt].pos.y + pTutorial[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pTutorial[nCnt].pos.x + pTutorial[nCnt].size.x, pTutorial[nCnt].pos.y + pTutorial[nCnt].size.y, 0.0f);
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
	g_pVtxBuffTutorial->Unlock();
	return S_OK;
}

void UninitTutorial(void)
{
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
	for (int nCnt = 0; nCnt < TUTORIAL_COMPONENT; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
	free(pTutorial);
}

void UpdateTutorial(void)
{
	if (GetkeyboardRelease(DIK_RETURN) == true)
		SetFade(FADE_OUT, MODE_MENU);
}

void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < TUTORIAL_COMPONENT; nCnt++)
	{
		if (pTutorial[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTutorial[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}
