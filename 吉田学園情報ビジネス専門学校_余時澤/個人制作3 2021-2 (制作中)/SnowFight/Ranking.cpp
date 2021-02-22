//=============================================================================
//
// [Ranking.cpp]
// Author : JITAKU YO
//
//=============================================================================
#include "Ranking.h"
#include "Fade.h"
#include "Dinput8.h"

//create buffer pointer
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;
//texture pointer
LPDIRECT3DTEXTURE9 g_pTextureRank[RANK_COMPONENT] = {};
POLYGON_2D *pRank;

HRESULT InitRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_2D *pVtx;
	pRank = (POLYGON_2D *)malloc(RANK_COMPONENT * sizeof(POLYGON_2D));

	pRank[0].bUse = true;
	pRank[0].pos = D3DXVECTOR3(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2, 0);
	pRank[0].size = D3DXVECTOR2(WIDTH_SCREEN / 2, HEIGHT_SCREEN / 2);

	//load texture
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/Texture/ScreenTransition/RankBackground.png", &g_pTextureRank[0])))return E_FAIL;

	//create vertex buffer
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANK_COMPONENT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRank, NULL))) return E_FAIL;

	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < RANK_COMPONENT; nCnt++)
	{
		pVtx[0].pos = D3DXVECTOR3(pRank[nCnt].pos.x - pRank[nCnt].size.x, pRank[nCnt].pos.y - pRank[nCnt].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pRank[nCnt].pos.x + pRank[nCnt].size.x, pRank[nCnt].pos.y - pRank[nCnt].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pRank[nCnt].pos.x - pRank[nCnt].size.x, pRank[nCnt].pos.y + pRank[nCnt].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pRank[nCnt].pos.x + pRank[nCnt].size.x, pRank[nCnt].pos.y + pRank[nCnt].size.y, 0.0f);
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
	g_pVtxBuffRank->Unlock();

	return S_OK;
}

void UninitRank(void)
{
	if (g_pVtxBuffRank != NULL)
	{			  
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}
	for (int nCnt = 0; nCnt < RANK_COMPONENT; nCnt++)
	{
		if (g_pTextureRank[nCnt] != NULL)
		{			  
			g_pTextureRank[nCnt]->Release();
			g_pTextureRank[nCnt] = NULL;
		}
	}
	free(pRank);
}

void UpdateRank(void)
{
	if (GetkeyboardTrigger(DIK_RETURN) == true)
		SetFade(FADE_OUT, MODE_MENU);
}

void DrawRank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < RANK_COMPONENT; nCnt++)
	{
		if (pRank[nCnt].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureRank[nCnt]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}